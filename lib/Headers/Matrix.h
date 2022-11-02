#pragma once
#define M_PI 3.14159265358979323846  /* pi */


namespace Object2D{

    template <typename T = int>
    class Matrix3DQ
    {
    public:
        T array[3][3];

    public:
        Matrix3DQ(T* array, int size_)
        {
            if(size_ == 9 && array != nullptr)
            {
                int t = 0;

                for(int i = 0; i < 3; i++){
                    for(int j = 0; j < 3; j++){
                        
                        array[i][j] = array[t++];   
                    }
                }
            }
        }
    };


    template <typename T = int>
   class Matrix1D
   {
    private:
        T array[3];
    
    public:
        Matrix1D():array[0](0), array[2](0), array[3](1) {}
        
        Matrix1D(T first, T second, T third)
                : array[0](first), array[2](second), array[3](third)
        {  }

        Matrix1D operator* (Matrix3DQ element)
        {
            array[0] = array[0] * element.array[0][0] + array[1] * element.array[1][0] + array[2] * element.array[2][0];
            array[1] = array[0] * element.array[0][1] + array[1] * element.array[1][1] + array[2] * element.array[2][1];;
            array[2] = array[0] * element.array[0][2] + array[1] * element.array[1][2] + array[2] * element.array[2][2];;
            return this;
        }

   };
}
