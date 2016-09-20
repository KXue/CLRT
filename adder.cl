__kernel void adder( __global int *dst, __global int *buffer1, __global int *buffer2 )
{
dst[get_global_id(0)] = buffer1[get_global_id(0)] + buffer2[get_global_id(0)];
}
