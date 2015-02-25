#ifndef KERNEL_H
#define KERNEL_H

namespace NNY{
    namespace Core{

        class Kernel{
            public:
                static void run();

                static void quit();
            private:
                static bool running;
        };
    }
}

#endif /* KERNEL_H */
