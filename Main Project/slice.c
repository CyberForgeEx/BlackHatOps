//This function make slicing the command provided by the user as cd 'cut' directory.

char *
str_cut(char str[], int slice_from, int slice_to)
{
    if(str[0] == '\0')
    {
        return NULL;
    }

    char *buffer;
    size_t str_len, buffer_len;

    if(slice_to < 0 && slice_from > slice_to)
    {
        str_len = strlen(str);

        if(abs(slice_to) > str_len - 1)
        {
            return NULL;
        }

        if(abs(slice_from) > str_len)
        {
            slice_from = (-1) * str_len;
        }

        buffer_len = slice_to - slice_from;
        str += (str_len + slice_from);
    }
    else if(slice_from >= 0 && slice_to > slice_from)
    {
        str_len = strlen(str);

        if(slice_from > str_len - 1)
        {
            return NULL;
        }

        buffer_len = slice_to - slice_from;
        str += slice_from;
    }
    else
    {
        return NULL;
    }

    buffer = calloc(buffer_len, sizeof(char));
    strncpy(buffer, str, buffer_len);
    return buffer;
}