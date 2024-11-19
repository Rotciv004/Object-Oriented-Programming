#include <stdio.h>
#include <time.h>
/*#include <crtbg.h>
nr_leaks = _crtDumpMemoryLeaks()
print("%d",nr_leaks)*/

// Structure to represent a date
struct Date {
    int day, month, year;
};

// Structure to represent a material
struct Material {
    char name[100], supplier[100];
    int quantity;
    struct Date expiration_date;
};

// Function to print details of a material
void print_material(struct Material material) {
    printf("Material Details:\n");
    printf("Name: %s\n", material.name);
    printf("Supplier: %s\n", material.supplier);
    printf("Quantity: %d\n", material.quantity);
    printf("Expiration Date: %d/%d/%d\n\n", material.expiration_date.day, material.expiration_date.month, material.expiration_date.year);
}

// Function to read the current date
void read_current_date(struct Date* current_date) {
    printf("Enter current date (DD MM YYYY): ");
    scanf("%d %d %d", &current_date->day, &current_date->month, &current_date->year);
}

// Function to read details of a material
void read_material_details(struct Material* material) {
    printf("Enter name of material: ");
    scanf("%s", material->name);

    printf("Enter supplier of material: ");
    scanf("%s", material->supplier);

    printf("Enter quantity of material: ");
    scanf("%d", &material->quantity);

    printf("Enter expiration date (DD MM YYYY): ");
    scanf("%d %d %d", &material->expiration_date.day, &material->expiration_date.month, &material->expiration_date.year);
    printf("\n\n");
}

// Function to verify if a material already exists in the list
int find_existing_material_index(struct Material material, struct Material materials_list[], int len_materials_list) {
    for (int index = 0; index < len_materials_list; ++index)
        if (strcmp(materials_list[index].name, material.name) == 0 &&
            strcmp(materials_list[index].supplier, material.supplier) == 0 &&
            materials_list[index].expiration_date.day == material.expiration_date.day &&
            materials_list[index].expiration_date.month == material.expiration_date.month &&
            materials_list[index].expiration_date.year == material.expiration_date.year)
            return index;

    return -1;
}

// Function to delete a material from the list
void delete_material(struct Material materials_list[], int* len_materials_list, int index) {
    for (int i = index; i < *len_materials_list - 1; ++i)
        materials_list[i] = materials_list[i + 1];

    *len_materials_list = *len_materials_list-1;

    printf("Material deleted successfully\n\n");
}

// Function to modify a material in the list
int modify_material(struct Material materials_list[], struct Material material, int len_material_list) {
    for (int index = 0; index < len_material_list; ++index)
        if (strcmp(materials_list[index].name, material.name) == 0) {
            materials_list[index] = material;
            return 1;
        }

    return 0;
}

// Function to list all expired materials
void list_all_expired_materials(struct Material materials_list[], int len_materials_list, struct Date current_date) {
    for (int index = 0; index < len_materials_list; ++index) {
        if (materials_list[index].expiration_date.year < current_date.year ||
            (materials_list[index].expiration_date.year == current_date.year &&
                materials_list[index].expiration_date.month < current_date.month) ||
            (materials_list[index].expiration_date.year == current_date.year &&
                materials_list[index].expiration_date.month == current_date.month &&
                materials_list[index].expiration_date.day < current_date.day)) {
            print_material(materials_list[index]);
        }
    }
}

// Function to list all expired materials containing a given string
void list_expired_materials_with_given_string(struct Material materials_list[], int len_materials_list, struct Date current_date, char string[]) {
    printf("%d", strstr(string, materials_list[0].supplier));
    
    for (int index = 0; index < len_materials_list; ++index) {
        if ((materials_list[index].expiration_date.year < current_date.year ||
            (materials_list[index].expiration_date.year == current_date.year &&
                materials_list[index].expiration_date.month < current_date.month) ||
            (materials_list[index].expiration_date.year == current_date.year &&
                materials_list[index].expiration_date.month == current_date.month &&
                materials_list[index].expiration_date.day < current_date.day)) &&
            (strstr(materials_list[index].name, string) != NULL || strstr(materials_list[index].supplier, string) != NULL)) {
            print_material(materials_list[index]);
        }
    }
}

// Function to display materials from a supplier in short supply
void display_materials_for_supplier(struct Material materials_list[], int len_materials_list, char supplier[], int quantity_threshold) {
    struct Material materials_below_threshold[999];
    int num_below_threshold = 0;

    for (int index = 0; index < len_materials_list; ++index) {
        if (strcmp(materials_list[index].supplier, supplier) == 0 && materials_list[index].quantity < quantity_threshold) {
            materials_below_threshold[num_below_threshold++] = materials_list[index];
        }
    }

    // Sort materials_below_threshold by quantity in ascending order
    for (int i = 0; i < num_below_threshold - 1; ++i) {
        for (int j = 0; j < num_below_threshold - i - 1; ++j) {
            if (materials_below_threshold[j].quantity > materials_below_threshold[j + 1].quantity) {
                struct Material temp = materials_below_threshold[j];
                materials_below_threshold[j] = materials_below_threshold[j + 1];
                materials_below_threshold[j + 1] = temp;
            }
        }
    }

    printf("Materials from supplier %s below quantity threshold %d:\n", supplier, quantity_threshold);
    for (int i = 0; i < num_below_threshold; ++i) {
        print_material(materials_below_threshold[i]);
    }
}

// Function to handle expired materials containing a string
void handle_expired_materials_with_string(struct Material materials_list[], int len_materials_list) {
    char string[100];
    int d;
    struct Date date;

    read_current_date(&date);

    printf("Input a string -> ");
    while ((d = getchar()) != '\n' && d != EOF) {}
    fgets(string, sizeof(string), stdin);

    if (string[0] == 'N') {
        list_all_expired_materials(materials_list, len_materials_list, date);
    }
    else {
        list_expired_materials_with_given_string(materials_list, len_materials_list, date, string);
    }
}

int main() {
    struct Material materials_list[999];
    int num_materials = 0;

    while (1) {
        printf("1. Add a material\n");
        printf("2. Delete a material\n");
        printf("3. Update a material\n");
        printf("4. See all expired materials that contain a given string\n");
        printf("5. Display materials from a supplier in short supply\n");
        printf("0. EXIT\n\n");

        int command;

        printf("Input a command -> ");
        scanf("%d", &command);
        printf("\n\n");

        if (command == 1) {
            printf("Add a material:\n");
            struct Material material;
            read_material_details(&material);

            int existing_index = find_existing_material_index(material, materials_list, num_materials);
            if (existing_index == -1) {
                materials_list[num_materials++] = material;
                printf("Material added successfully\n\n");
            }
            else {
                materials_list[existing_index].quantity += material.quantity;
                printf("Material updated successfully\n\n");
            }
        }
        else if (command == 2) {
            printf("Delete a material:\n");
            struct Material material;
            read_material_details(&material);

            int existing_index = find_existing_material_index(material, materials_list, num_materials);
            if (existing_index != -1) {
                delete_material(materials_list, &num_materials, existing_index);
            }
            else {
                printf("This material doesn't exist!\n\n");
            }
        }
        else if (command == 3) {
            printf("Update a material:\n");
            struct Material material;
            read_material_details(&material);

            if (modify_material(materials_list, material, num_materials)) {
                printf("Material was successfully modified!\n\n");
            }
            else {
                printf("Material doesn't exist!\n\n");
            }
        }
        else if (command == 4) {
            printf("See all expired materials that contain a given string:\n");
            handle_expired_materials_with_string(materials_list, num_materials);
        }
        else if (command == 5) {
            char supplier[100];
            int quantity_threshold;
            printf("Enter supplier name: ");
            scanf("%s", supplier);
            printf("Enter quantity threshold: ");
            scanf("%d", &quantity_threshold);

            display_materials_for_supplier(materials_list, num_materials, supplier, quantity_threshold);
        }
        else if (command == 0) {
            printf("Exit!\n");
            break;
        }
        else {
            printf("Invalid command!\n\n");
        }
    }

    return 0;
}