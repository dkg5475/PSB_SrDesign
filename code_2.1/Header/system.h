#ifndef SYSTEM_H
#define SYSTEM_H

/* Function prototypes*/
void osc32k_init               (void);
void osc48m_init               (void);
void gclk1_init                (void);
void dpll_init                 (void);
void gclk0_init                (void);
void mclk_init                 (void);
void peripheral_clk_init       (void);
void pin_cfg                   (void);


#endif