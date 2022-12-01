#include "tbutils.h"
#include "op.h"
#include "net.h"
#include <string>

#ifdef _WIN32
#include <windows.h>
DWORD st, et;
#endif

#ifdef __linux__
#include <sys/time.h>
timeval st, et;
#endif

int main()
{
    mylenet::DATA _img[32][32] = {0};
    mylenet::INPUT img[32][32] = {0};
    int rst;
    std::string str = "./imgs/img_";
    std::string img_path = "./imgs/img_";

    #ifdef _WIN32
    DWORD elapsed_time = 0;
    #endif
	#ifdef __linux__
    double elapsed_time = 0;
	#endif

    for (int i = 0; i < 50; i++) {
        img_path = str + std::to_string(i) + ".txt";
        txt2arr(img_path, _img);
        copy_arr(img, _img);

        #ifdef _WIN32
        st = GetTickCount();
        #endif
		#ifdef __linux__
        gettimeofday(&st, NULL);
		#endif

        rst = lenet(img);

        #ifdef _WIN32
        et = GetTickCount();
        elapsed_time += et - st;
        #endif
		#ifdef __linux__
        gettimeofday(&et, NULL);
        elapsed_time += (et.tv_sec - st.tv_sec) * 1000 + (et.tv_usec - st.tv_usec) / 1000;
		#endif

        std::cout << rst << " ";
    }
    std::cout << std::endl;

    std::cout << "\nPrediction of 50 pictures takes time "<< elapsed_time << " ms\n";

    return 0;
}
