#ifndef _ISHACKER_ISHSLEEP_H
#define _ISHACKER_ISHSLEEP_H

bool ishacker_cm_mgr_screen_on_get(void);
bool ishacker_system_irq_wakeup_actual_get(void);
void ishacker_system_irq_wakeup_actual_set(bool val);

#endif /* _ISHACKER_ISHSLEEP_H */
