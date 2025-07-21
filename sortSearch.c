#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "include/input_utils.h"

#define MAX_CONTACTS 10

typedef struct {
    char name[50];
    char phone[15];
    char email[50];
} Contact;

int search_index(Contact contacts[], int count, const char *name);

void del_contact(Contact contacts[], int *count, int index);

void print_contacts(const Contact contacts[], int count);

void usage(const char *prog);


int main(int argc, char *argv[]) {
    Contact contacts[MAX_CONTACTS];
    int contact_count = 0;

    if (argc > 1) {
        const char *cmd = argv[1];
        if (strcmp(cmd, "list") == 0) {
            if (argc != 2) usage(argv[0]);
            print_contacts(contacts, contact_count);
        }
        else if (strcmp(cmd, "add") == 0) {
            if (argc != 5) usage(argv[0]);
            if (contact_count >= MAX_CONTACTS) {
                fprintf(stderr, "\nList full\n"); return 1;
            }
            strncpy(contacts[contact_count].name,  argv[2], sizeof contacts[0].name-1);
            strncpy(contacts[contact_count].phone, argv[3], sizeof contacts[0].phone-1);
            strncpy(contacts[contact_count].email, argv[4], sizeof contacts[0].email-1);
            contact_count++;
            printf("\nAdded %s\n", argv[2]);
        }
        else if (strcmp(cmd, "search") == 0) {
            if (argc != 3) usage(argv[0]);
            int idx = search_index(contacts, contact_count, argv[2]);
            if (idx >= 0) printf("\nFound: %s, %s, %s\n",
                    contacts[idx].name,
                    contacts[idx].phone,
                    contacts[idx].email);
            else 
            printf("\n");
            printf("\n%s not found\n", argv[2]);
        }
        else if (strcmp(cmd, "remove") == 0) {
            if (argc != 3) usage(argv[0]);
            int idx = search_index(contacts, contact_count, argv[2]);
            if (idx >= 0) {
                del_contact(contacts, &contact_count, idx);
                printf("\nRemoved %s\n", argv[2]);
            } else printf("%s not found\n", argv[2]);
        }
        else usage(argv[0]);
    } else {
    // interactive mode
    char *cmd;
    printf("\nWelcome to the Interactive Contact Manager (max %d contacts)\n", MAX_CONTACTS);
    while (1) {
        cmd = get_string("\nEnter command (list, add, search, remove, quit): ");

        if (strcmp(cmd, "list") == 0) {
            print_contacts(contacts, contact_count);
            continue;

        } else if (strcmp(cmd, "add") == 0) {
            if (contact_count >= MAX_CONTACTS) {
                printf("Contact list is full!\n");
                continue;
            }
            // Prompt and copy name
            char *name = get_string("\nEnter name: ");
            strncpy(contacts[contact_count].name, name, sizeof contacts[0].name - 1);
            contacts[contact_count].name[sizeof contacts[0].name - 1] = '\0';
            // Prompt and copy phone
            char *phone = get_string("Enter phone: ");
            strncpy(contacts[contact_count].phone, phone, sizeof contacts[0].phone - 1);
            contacts[contact_count].phone[sizeof contacts[0].phone - 1] = '\0';
            // Prompt and copy email
            char *email = get_string("Enter email: ");
            strncpy(contacts[contact_count].email, email, sizeof contacts[0].email - 1);
            contacts[contact_count].email[sizeof contacts[0].email - 1] = '\0';

            contact_count++;
            printf("\n---------------------------\n");
            printf("Contact added. Total now: %d\n", contact_count);
            printf("---------------------------\n");

        } else if (strcmp(cmd, "search") == 0) {
            char *name = get_string("\nEnter name to search: ");
            int idx = search_index(contacts, contact_count, name);
            if (idx >= 0) {
                printf("\nFound at index %d:\n", idx);
                printf("\n");
                printf("  Name:  %s\n  Phone: %s\n  Email: %s\n",
                       contacts[idx].name,
                       contacts[idx].phone,
                       contacts[idx].email);
            } else {
                printf("'%s' not found.\n", name);
            }

        } else if (strcmp(cmd, "remove") == 0) {
            char *name = get_string("\nEnter name to remove: ");
            int idx = search_index(contacts, contact_count, name);
            if (idx >= 0) {
                del_contact(contacts, &contact_count, idx);
                printf("\nContact removed. Total now: %d\n", contact_count);
            } else {
                printf("'%s' not found.\n", name);
            }

        } else if (strcmp(cmd, "quit") == 0) {
            printf("\nExiting....\n");
            printf("\n");
            break;

        } else {
            printf("\nUnknown command '%s'.\n", cmd);
        }
    }
    return 0;
    }
}

// usage instructions
void usage(const char *prog) {
    fprintf(stderr,
            "Usage:\n"
            "  %s interactive mode\n"
            "  %s list  \n"
            "  %s add <name> <phone> <email> \n"
            "  %s search <name> \n"
            "  %s remove <name> \n"
            "  %s quit",
            prog, prog, prog, prog, prog, prog);
    exit(1);
}

// function to search the index of a contact by name 
int search_index(Contact contacts[], int count, const char *name) {
    for (int i = 0; i < count; i++) {
        if (strcmp(contacts[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

// function delete the contact at index
void del_contact(Contact contacts[], int *count, int index) {
    memmove(&contacts[index], &contacts[index + 1],
            (size_t)(*count - index - 1) * sizeof(Contact));
    (*count)--; // this reflects the removal
}

// function that prints all contacts (name, phone, email)
void print_contacts(const Contact contacts[], int count) {
    printf("\n-----------------------\n");
    printf("Number of Contacts (%d): \n", count);
    printf("-----------------------\n");
    for (int i = 0; i < count; i++) {
        printf("\n");
        printf("Name:  %s\n", contacts[i].name);
        printf("Phone: %s\n", contacts[i].phone);
        printf("Email: %s\n", contacts[i].email);
    }
}