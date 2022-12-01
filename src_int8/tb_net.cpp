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
    float _img[32][32] = {0};
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

    int rst_vec[50];

    int tb_iter = 50;

    for (int i = 0; i < tb_iter; i++) {
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
        rst_vec[i] = rst;

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

    int gold[50] = {7, 2, 1, 0, 4, 1, 4, 9, 5, 9, 0, 6, 9, 0, 1, 5, 9, 7, 3, 4, 9, 6, 6, 5, 4, 0, 7, 4, 0, 1, 3, 1, 3, 4, 7, 2, 7, 1, 2, 1, 1, 7, 4, 2, 3, 5, 1, 2, 4, 4};
    int coincide = 0;
    for (int i = 0; i < tb_iter; i++) {
    	if (rst_vec[i] == gold[i]) {
    		coincide++;
    	}
    }

    std::cout << "Precision = " << (double) coincide / tb_iter * 100. << "%" << std::endl;

    return 0;
}
