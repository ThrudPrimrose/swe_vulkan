#include <vector>
#include <iostream>

template <typename U>
U absolute(U d){
    if (d<0) return -d; else return d;
}

 /*! \fn int getClose(std::vector<T> arr,int beg, int bound, U search)
    * \brief BinarySearch to get the closest value to the given input
    * 
    * If the beg is 0 and the bound is the size of the array, the whole array is search, otherwise the subest [beg,bound) will be searched
    * \tparam T type of the elements in array, should be double or float
    * \tparam U type of the input, should be double or float
    * \param arr std::vector initialized in the scenario, which is the array to search
    * \param beg begin index of the search
    * \param bound  end index of the search
    * \param search the value to be searched
    * \return Closest value to search input
    */
template <typename T, typename U>
int getClose(std::vector<T> arr,int beg, int bound, U search)
{
    bound=bound-1;
    if(bound>arr.size()){
        std::cout<<"wtf going on"<<std::endl;
        return -10;
    }
    if (search < arr[0]){
        return 0;

    }
    if(search > arr[bound]){
        return bound;
    }

    while(beg<=bound){
        int mid = (beg+bound)/2;
        if(search<arr[mid]){
            bound = mid-1;
        }else if(search>arr[mid]){
            beg = mid+1;
        }else{
            return mid;
        }
    }

     if(absolute(search-arr[beg])< abssolute(arr[bound]-search)){
            return beg;
        }else{
            return bound;
    }

}

 /*! \fn int getClose(T* arrp,int beg, int bound, U search)
    * \brief BinarySearch to get the closest value to the given input
    * 
    * If the beg is 0 and the bound is the size of the array, the whole array is search, otherwise the subest [beg,bound) will be searched.
    * \tparam T type of the element in an array, should be float or double
    * \tparam U type of the element we search, should be float or double
    * \param arrp pointer to array 
    * \param beg begin index for search
    * \param bound end index for search
    * \param search value to be searched
    * \return
    */
template <typename T, typename U>
int getClose(T* arrp,int beg, int bound, U search)
{
    int offel = sizeof(T);
    bound=bound-1;
    if (search < *arrp){
        return 0;

    }
    if(search > *(arrp+(offel*bound))){
        return bound;
    }

    while(beg<=bound){
        int mid = (beg+bound)/2;
        if(search< *(arrp+(offel*mid))){
            bound = mid-1;
        }else if(search> *(arrp+(offel*mid)))
        {
            beg = mid+1;
        }else{
            return mid;
        }
    }

     if(absolute(search-*(arrp+(offel*beg)))< absolute(*(arrp+(offel*bound))-search)){
            return beg;
        }else{
            return bound;
    }

}
