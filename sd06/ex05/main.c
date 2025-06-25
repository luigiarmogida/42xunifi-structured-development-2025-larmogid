#include <stdio.h>
#include <stdlib.h>
#include "contact_list.h"
#include "io_handler.h"
#include "ui_menu.h"

int main(int argc, char **argv)
{
	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s contacts.csv\n", argv[0]);
		return 1;
	}

	const char *filename = argv[1];
	t_contact_list *list = create_contact_list();
	if (!list)
	{
		fprintf(stderr, "Error: failed to allocate contact list.\n");
		return 1;
	}

	if (!load_contacts(filename, list))
	{
		free_contact_list(list);
		return 1;
	}

	run_menu(list, filename);

	free_contact_list(list);
	return 0;
}
