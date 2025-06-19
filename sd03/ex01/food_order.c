#include "food_order.h"
#include <stdlib.h>

// Livello intermedio: decidi quale tipo di conferma serve
static int determine_confirmation_type(struct OrderRequest *request) {
    return check_restaurant_status(request); // 1 = standard, 0 = preorder
}

// Livello intermedio: genera la conferma
static struct OrderConfirmation *generate_order_confirmation(int is_open) {
    if (is_open)
        return create_standard_confirmation();
    else
        return create_preorder_confirmation();
}

// Livello intermedio: invia la conferma
static void send_confirmation(struct OrderConfirmation *confirmation) {
    send_confirmation_notification(confirmation);
}

// Livello intermedio: pulizia memoria
static void cleanup_confirmation(struct OrderConfirmation *confirmation) {
    free(confirmation);
}

// Livello alto: gestisce il processo completo
int process_food_order(struct OrderRequest *request) {
    if (!request)
        return 0;

    int is_open = determine_confirmation_type(request);

    struct OrderConfirmation *confirmation = generate_order_confirmation(is_open);
    if (!confirmation)
        return 0;

    send_confirmation(confirmation);
    cleanup_confirmation(confirmation);

    return 1;
}