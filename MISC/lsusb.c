#include <libusb-1.0/libusb.h>
#include <assert.h>
#include <stdio.h>

int main()
{
    libusb_context *context;
    libusb_device **list;
    ssize_t         count;
    size_t          index;

    if (libusb_init(&context) != 0)
     {
        fprintf(stderr, "error: intializing `libusb'");
        return -1;
     }

    count = libusb_get_device_list(context, &list);
    for (index = 0; index < count; ++index)
    {
        struct libusb_device           *device;
        struct libusb_device_descriptor descriptor;
        char                            buffer[256];
        struct libusb_device_handle    *handle;
        int                             result;

        device = list[index];
        if ((result = libusb_get_device_descriptor(device, &descriptor)) != 0)
         {
            fprintf(stderr, "error(%d): reading descriptor\n", result);
            continue;
         }

        if ((result = libusb_open(device, &handle)) != 0)
         {
            fprintf(stderr, "error(%d): openning device 0x%04X:0x%04X\n", 
                result, descriptor.idVendor, descriptor.idProduct);
            continue;
         }
        fprintf(stdout, "\ndevice #: %zu 0x%04X:0x%04X\n", 
            index, descriptor.idVendor, descriptor.idProduct);

        result = libusb_get_string_descriptor_ascii(
            handle,
            descriptor.iProduct,
            (unsigned char *)buffer,
            sizeof(buffer)
        );
        if (result != 0)
            fprintf(stdout, "\tproduct     : %s\n", buffer);
        result = libusb_get_string_descriptor_ascii(
            handle,
            descriptor.iManufacturer,
            (unsigned char *)buffer,
            sizeof(buffer)
        );
        if (result != 0)
            fprintf(stdout, "\tmanufacturer: %s\n", buffer);
        libusb_close(handle);
    }
   return 0;
}
