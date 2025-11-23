void Delay(unsigned int ms) //@11.0592MHz
{
    unsigned char i, j;
    __asm nop
        __endasm;

    while (ms--)
    {
        i = 2;
        j = 199;
        do
        {
            while (--j)
                ;
        } while (--i);
    }
}