#ifdef __cplusplus
extern "C" {
#endif

int ___errno;

/* TODO: figure out a proper way for this to be thread-local */
int *__errno(void)
{
	return &___errno;
}

#ifdef __cplusplus
}
#endif
