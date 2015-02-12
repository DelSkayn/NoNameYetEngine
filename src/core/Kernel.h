#ifndef KERNEL_H
#define KERNEL_H

class Kernel{
    public:
        static void run();

        static void quit();
    private:
        static bool running;
};

#endif /* KERNEL_H */
