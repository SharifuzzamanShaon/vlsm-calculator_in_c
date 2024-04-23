#include <stdio.h>
#include <stdlib.h>

int main()
{
    char ip_address_str[16];
    printf("Enter IP address (e.g., 192.168.1.10): ");
    scanf("%15s", ip_address_str);

    // Variables to store binary representation
    int binary_rep[32]; // Assuming IPv4 address

    // Parse the IP address string and convert each octet to binary
    unsigned char ip_addr[4]; // Assuming IPv4 address
    sscanf(ip_address_str, "%hhu.%hhu.%hhu.%hhu", &ip_addr[0], &ip_addr[1], &ip_addr[2], &ip_addr[3]);


    printf("\n");

    // find the subnet mask
    int subnet_mask_decimal=0;
    int subnet_mask[4] = {0}; // Array to store the four octets of the subnet mask
    printf("Enter subnet mask (e.g. /24)");
    scanf("%d",&subnet_mask_decimal);
    // Calculate the subnet mask
    for (int i = 0; i < subnet_mask_decimal; ++i)
    {
        int index = i / 8;
        subnet_mask[index] |= (1 << (7 - (i % 8)));
    }
    // Print the subnet mask in the format "255.255.255.0"
    printf("\n %d.%d.%d.%d\n", subnet_mask[0], subnet_mask[1], subnet_mask[2], subnet_mask[3]);
    int thirdOctal;

    //allocate subnets
    int totalSubent;
    printf("Total Subnet you need:");
    scanf("%d",&totalSubent);
    int totalHost[totalSubent];
    for(int i=0; i<totalSubent; i++)
    {
        printf("%d number network: Insert total host number:",i+1);
        scanf("%d",&totalHost[i]);
    }
    /// Sorting the array
    for(int i=0; i<totalSubent-1; i++)
    {
        for(int j=0; j<totalSubent-i-1; j++)
        {
            if(totalHost[j]<totalHost[j+1])
            {
                int temp = totalHost[j];
                totalHost[j]=totalHost[j+1];
                totalHost[j+1]= temp;
            }
        }
    }
    printf("\n\n");

    //check Validation of subnet mask
    int num_of_host_need;
    for(int i=0; i <totalSubent; i++)
    {
        num_of_host_need += totalHost[i];
    }
    printf("Your subnets need %d hosts\n", num_of_host_need);
    int num_of_host_have;
    num_of_host_have = pow(2, 32-subnet_mask_decimal)-2;
    printf("Your Network have %d hosts\n", num_of_host_have);

    if(num_of_host_have < num_of_host_need)
    {
        double n = log2(num_of_host_need);
        int minBit = ceil(n);
        int requiredSubnet = 32-minBit;
        printf("Subnets will not fit into that network");
        printf("Minimum /%d subnet mask is required", requiredSubnet);
        printf("\n\n");
        exit(1);
    }

        // calculate the subnet
        //128 64 32 16 8 4 2 1
        calculateSubnet(totalSubent, totalHost, ip_addr);
    return 0;
}

void calculateSubnet(int totalSubent, int totalHost[], int ip_addr[]){
            for (int i = 0; i < totalSubent; i++)
        {
            printf("Network %d: Total hosts = %d\n", i + 1, totalHost[i]);
            int hosts = totalHost[i]+2;
            int bits;
            int sub_ip_addr;
            if(hosts==4)
            {
                sub_ip_addr = 4;
            }
            else if(hosts>4 && hosts<=7 )
            {
                bits=3;
                sub_ip_addr= pow(2,3);
            }
            else if(hosts>7 && hosts<=15)
            {
                bits =4;
                sub_ip_addr= pow(2,4);
            }
            else if(hosts>15 && hosts<=31)
            {
                bits =5;
                sub_ip_addr=pow(2,5);
            }
            else if(hosts>31 && hosts<=63)
            {
                bits =6;
                sub_ip_addr= pow(2,6);
            }
            else if(hosts>63 && hosts<=127)
            {
                bits =7;
                sub_ip_addr= pow(2,7);
            }
            else if(hosts>127 && hosts<=256)
            {
                bits =8;
                sub_ip_addr= pow(2,8);
            }
            int end_next_sub_ip_addr, start_sub_ip_addr;
            if(totalHost[i] == 0)
            {
                start_sub_ip_addr =ip_addr[3];
            }
            else
            {
                start_sub_ip_addr = end_next_sub_ip_addr;
            }
            if(end_next_sub_ip_addr!=0)
            {
                end_next_sub_ip_addr = end_next_sub_ip_addr;
            }
            else
            {
                end_next_sub_ip_addr=0;
            }
            printf("N/A %d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2], start_sub_ip_addr);
            //printf("Subnet mask %d.%d.%d.%d\n", subnet_mask[0], subnet_mask[1], subnet_mask[2], sub_ip_addr);
            printf("Valid range: %d.%d.%d.%d", ip_addr[0], ip_addr[1], ip_addr[2], start_sub_ip_addr+1);
            printf(" - %d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2],end_next_sub_ip_addr + sub_ip_addr-2);
            printf("B/A %d.%d.%d.%d\n", ip_addr[0], ip_addr[1], ip_addr[2], end_next_sub_ip_addr + sub_ip_addr-1);
            end_next_sub_ip_addr = end_next_sub_ip_addr + sub_ip_addr;
            printf("\n\n");
        }
}
