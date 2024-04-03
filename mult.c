#include <stdio.h>
#include <stdint.h>

void multiply_32bit_unsigned(uint32_t num1, uint32_t num2, uint32_t *result_low, uint32_t *result_high) {
    // Perform sign extension
    uint16_t num1_low = num1 & 0xFFFF;
    uint16_t num1_high = (num1 >> 16) & 0xFFFF;
    uint16_t num2_low = num2 & 0xFFFF;
    uint16_t num2_high = (num2 >> 16) & 0xFFFF;
    
    // Perform multiplication in parts
    uint32_t part1 = (uint32_t)num1_low * num2_low;
    uint32_t part2 = (uint32_t)num1_low * num2_high;
    uint32_t part3 = (uint32_t)num1_high * num2_low;
    uint32_t part4 = (uint32_t)num1_high * num2_high;
    
    // Calculate the high and low parts of the result
    uint32_t temp = (part2 >> 16) + (part3 >> 16);
    uint32_t temp1 = ((part2 << 16) >> 16) + ((part3 << 16) >> 16) + (part1 >> 16);
    *result_low = (part1 & 0xFFFF) | ((temp1 & 0xFFFF) << 16);
    *result_high = (part4)+(temp)+((temp1 & 0xffff0000) >> 16);
}

int main() {
    uint32_t num1;// 0xBC614E; //12345678 abs(num1_i)
    uint32_t num2 = 0x05397FB1; // 0x05397FB1; //87654321
    int32_t num1_i = 0xFF439EB2;// 0xFF439EB2; //-12345678 
    int32_t num2_i = 0x05397FB1;// 0x05397FB1; //87654321
    int32_t num3_i;// = 0xBC614E; //12345678
    uint32_t result_low;
    uint32_t result_high;
    
    num1 = (uint32_t)(0 - num1_i);
    num3_i = (0 - num1_i);
    multiply_32bit_unsigned(num1, num2, &result_low, &result_high);
    
    //result when num1 = -12345678 and num2 = 87654321
    printf("Low Register: %x\n", (0-((int32_t)result_low)));

    if(result_low)
        printf("High Register: %x\n", (-1 - ((int32_t)result_high)));
    else
        printf("High Register: %x\n", (0 - ((int32_t)result_high)));

    printf("64bit result: %llx\n", (((long long)num1_i)*((long long)num2_i)));

    //result when num1 = 12345678 and num2 = 87654321
    printf("Low Register: %x\n", ((int32_t)result_low));
    printf("High Register: %x\n",((int32_t)result_high));
    printf("64bit result: %llx\n", (((long long)num3_i) * ((long long)num2_i)));
    
    return 0;
}
