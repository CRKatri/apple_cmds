CFLAGS+=-DDAEMON_UID=1 -DDAEMON_GID=1 -DDEFAULT_AT_QUEUE=\'a\' -DDEFAULT_BATCH_QUEUE=\'b\' -DPERM_PATH=\"/usr/lib/cron/\" -DPRIVATE

.include "../Makefile.inc"
