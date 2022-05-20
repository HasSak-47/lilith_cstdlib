#include <vector.h>

/**
 * @brief generic push function
 * 
 * @param vector 
 * @param data 
 * @param d_size 
 * @param mem 
 * @return int 
 */
int __push(vector_byte* vector, byte* data, size_t d_size, dyn_mem* mem){
	void* buffer = vector->data;
	buffer = mem->rll(buffer, d_size * (vector->size + 1));
	if(buffer == NULL)
		return -1;
	
	vector->data = buffer;
	//should have usen memcopy but meh
	for (size_t i = 0; i < d_size; ++i)
		vector->data[(vector->size * d_size) + i] = data[i];
	vector->size++;

	return 0;
}

/**
 * @brief generic pop function
 * 
 * @param vector 
 * @param d_size 
 * @param mem 
 * @return int 
 */
int  __pop(vector_byte* vector, size_t d_size, dyn_mem* mem){
	void* buffer = vector->data;
	buffer = mem->rll(buffer, sizeof(byte) * (vector->size - 1));
	if(buffer == NULL)
		return -1;

	return 0;

}

/**
 * @brief can't be fucked to implement it lmao
 * 
 * @param vector 
 * @param data 
 * @param d_size 
 * @param index 
 * @param mem 
 * @return int 
 */
int __insert(vector_byte* vector, byte* data, size_t d_size, size_t index, dyn_mem* mem){
	return -1;
}

/**
 * @brief can't be fucked to implement it lmao
 * 
 * @param vector 
 * @param data 
 * @param d_size 
 * @param index 
 * @param mem 
 * @return int 
 */
int __pop_in(vector_byte* vector, size_t index, dyn_mem* mem){
	return -1;
}
