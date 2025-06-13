#ifndef FOOD_ORDER_H
#define FOOD_ORDER_H

struct OrderRequest {
    // Dettagli dell’ordine, non specificati
};

struct OrderConfirmation {
    // Dettagli della conferma, non specificati
};

int check_restaurant_status(struct OrderRequest *request);
struct OrderConfirmation *create_standard_confirmation(void);
struct OrderConfirmation *create_preorder_confirmation(void);
void send_confirmation_notification(struct OrderConfirmation *confirmation);

int process_food_order(struct OrderRequest *request);

#endif
