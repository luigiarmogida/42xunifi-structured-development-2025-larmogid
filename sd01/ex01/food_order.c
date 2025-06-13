#include "food_order.h"
#include <stdlib.h>

int process_food_order(struct OrderRequest *request) {
    if (!request)
        return 0;

    int is_open = check_restaurant_status(request);
    struct OrderConfirmation *confirmation;

    if (is_open)
        confirmation = create_standard_confirmation();
    else
        confirmation = create_preorder_confirmation();

    if (!confirmation)
        return 0;

    send_confirmation_notification(confirmation);
    free(confirmation);

    return 1;
}
