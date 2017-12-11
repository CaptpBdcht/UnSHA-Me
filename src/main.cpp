#include "../include/arguments.hpp"
#include "../include/threaded-bruteforce.hpp"

// int main(int argc, char **argv) {

//     Arguments arguments;

//     arguments.analyseArguments(argc, argv);

//     ThreadedBruteforce tbf(
//         arguments.getThreadsNumber(),
//         arguments.getHashedPassword()
//     );

//     return EXIT_SUCCESS;
// }

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <cassert>

#define MIN_WORD_SIZE 1
#define MAX_WORD_SIZE 20

class Printer {
public:
    Printer() : mutex(), cv() {}

    void print(std::string message) {
        {
            std::unique_lock<std::mutex> lock(mutex);
            std::cout << message << std::endl;
        }
        cv.notify_one();
    }

private:
	std::mutex mutex;
	std::condition_variable cv;
};

class ProducerConsumer {
public:
    using Queue = std::queue<char*>;

	ProducerConsumer(
        const uint8_t nbProducer = 1,
        const uint8_t nbConsumer = 1,
        const std::string hashedPassword = ""
    ) :
    queue(),
    printer(),
    mutex(),
    cv(),
    nbProducer(nbProducer),
    nbConsumer(nbConsumer),
    hashedPassword(hashedPassword),
    producers(nbProducer),
    consumers(nbConsumer)
    {
		printer.print("ProducerConsumer::ProducerConsumer() : starting producers");
		for (uint8_t i = 0; i < nbProducer; ++i) {
			producers.emplace_front(std::thread(&ProducerConsumer::produce, this, i));
		}

		printer.print("ProducerConsumer::ProducerConsumer() : starting consumers");
		for (uint8_t i = 0; i < nbConsumer; ++i) {
			consumers.emplace_front(std::thread(&ProducerConsumer::consume, this, i));
		}
	}
	
	~ProducerConsumer() {
	    for (uint8_t i = 0; i < nbProducer; ++i) producers[i].join();
	    for (uint8_t i = 0; i < nbConsumer; ++i) consumers[i].join();
	    
	    printer.print("ProducerConsumer::~ProducerConsumer() Total produced: " + std::to_string(nbProducedSum));
	    printer.print("ProducerConsumer::~ProducerConsumer() Total consumed: " + std::to_string(nbConsumedSum));
	}

private:
    Queue queue;
    Printer printer;
	std::mutex mutex;
	std::condition_variable cv;
	const uint8_t nbProducer;
    const uint8_t nbConsumer;
    const std::string hashedPassword;
	std::deque<std::thread> producers;
	std::deque<std::thread> consumers;
	uint8_t nbFinishedProducer = 0;
	uint64_t nbConsumedSum = 0;
	uint64_t nbProducedSum = 0;
    bool foundWord;
    
    const char *alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 ";
	
    void produce(const uint8_t id) {
        printer.print("produce id=" + std::to_string(unsigned(id)));

        for (uint8_t wordLen = id; wordLen < MAX_WORD_SIZE; wordLen += nbConsumer) {
            double start = omp_get_wtime();

            generateWordsByLength(wordLen);

            double end = omp_get_wtime();

            printer.print("Word Len : " + std::to_string(wordLen));
            printer.print("Executed Time : " + std::to_string(end - start));
        }
        
        {
            std::lock_guard<std::mutex> lock(mutex);
            ++nbFinishedProducer;
            printer.print("produce id=" + std::to_string(unsigned(id)) + " done !");
            cv.notify_all();
        }
    }

    bool generateWordsByLength(uint8_t wordLen) {

        std::vector<uint8_t> indexesVector(wordLen, 0);

        while (true) {

            char *generatedWord = static_cast<char *>(malloc(indexesVector.size()));

            for (uint8_t i = 0; i < indexesVector.size(); ++i)
                generatedWord[i] = alphabet[indexesVector[i]];

            printer.print("Produced: " + std::string(generatedWord));

            {
                std::lock_guard<std::mutex> lock(mutex);
                queue.push(generatedWord);
                ++nbProducedSum;
            }

            cv.notify_one();

            for (long i = indexesVector.size() - 1;; --i) {

                if (i < 0) return true;

                ++indexesVector[i];

                if (indexesVector[i] == strlen(alphabet))
                    indexesVector[i] = 0;
                else
                    break;
            }

            if (generatedWord != nullptr) free(generatedWord);
        }
    }

    void consume(const uint8_t id) {
        printer.print("consume id=" + std::to_string(unsigned(id)));
        uint64_t consumed = 0;
        
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        
        while (true) {
            {
                std::unique_lock<std::mutex> lock(mutex);
                cv.wait(lock, [&] {
                    return !queue.empty() || foundWord;
                });
                
                if (foundWord) break;

                assert(queue.size() > 0);
                assert(!foundWord);

                // printer.print("Consumed: " + std::string(queue.front()));
            
                bool isSearchWord = computeSHA256(queue.front(), sha256);
                queue.pop();
                ++consumed;

                if (isSearchWord) {
                    printer.print("Found word: " + std::string(queue.front()));
                    foundWord = true;
                }
            }
        }
        
        {
            std::unique_lock<std::mutex> lock(mutex);
            assert(queue.size() == 0 || foundWord);
            nbConsumedSum += consumed;
        }
        
        printer.print("consume id=" + std::to_string(unsigned(id)) + " done ! consumed=" + std::to_string(consumed));
    }


    bool computeSHA256(char *wordToHash, SHA256_CTX sha256) {

        printer.print("Computing: " + std::string(wordToHash));

        uint8_t hash[SHA256_DIGEST_LENGTH];
        std::stringstream hashedWord;

        SHA256_Update(&sha256, wordToHash, strlen(wordToHash));
        SHA256_Final(hash, &sha256);

        for (uint8_t i : hash) {
            hashedWord << std::hex << std::setw(2) << std::setfill('0') << (int) i;
        }

        return hashedWord.str() == hashedPassword;
    }
};


int main() {
    // 1 1 'help'
	ProducerConsumer producerConsumer(
        2, 1,
        "106a5842fc5fce6f663176285ed1516dbb1e3d15c05abab12fdca46d60b539b7"
    );

	return 0;
}
