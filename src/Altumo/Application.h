#ifndef ALTUMO_APPLICATION_H
#define ALTUMO_APPLICATION_H



namespace Altumo{

    class Application{

        public:
            Application();
            ~Application();

        protected:
            FastCgiRecordType type;
            unsigned long data_size;
            char *data;

    };

}



#endif //ALTUMO_APPLICATION_H
