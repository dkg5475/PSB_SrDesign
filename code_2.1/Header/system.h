#ifndef SYSTEM_H
#define SYSTEM_H

/* Function prototypes*/
void system_init                      (void);
void nvic_init                        (void);
void nvic_int_disable                 (void);
void nvic_int_enable                  (void);
void supc_init                        (void);
void chip_erase                       (void);

#endif