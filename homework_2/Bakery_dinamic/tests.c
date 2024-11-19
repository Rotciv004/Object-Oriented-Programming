#include "tests.h"

void test_createMaterial()
{
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    // Assert statements to check if the material was created correctly
    assert(strcmp(getName(material), "Test Material") == 0);
    assert(strcmp(getSupplier(material), "Test Supplier") == 0);
    assert(getQuantity(material) == 10);
    assert(getDay(material) == 1);
    assert(getMonth(material) == 1);
    assert(getYear(material) == 2022);

    freeMaterial(material);
}

void test_freeMaterial()
{
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    freeMaterial(material);

    // Assert statement to check if the material was freed correctly
    assert(material == NULL);
}

void test_createRepo()
{
    Repo* repo = createRepo(10, &freeMaterial);

    // Assert statements to check if the repo was created correctly
    assert(getCapacity(repo) == 10);
    assert(getLen(repo) == 0);

    freeRepo(repo);
}

void test_freeRepo()
{
    Repo* repo = createRepo(10, &freeMaterial);

    freeRepo(repo);

    // Assert statement to check if the repo was freed correctly
    assert(repo == NULL);
}

/*void test_addElem()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    addElem(repo, material, 0);

    // Assert statements to check if the material was added correctly
    //assert(getLen(repo) == 1);
    //assert(equalMaterials(getElem_for_position(repo, 0), material));

    freeRepo(repo);
}*/

void test_deleteElem()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    addElem(repo, material, 0);
    deleteElem(repo, 0);

    // Assert statements to check if the material was deleted correctly
    assert(getLen(repo) == 0);

    freeRepo(repo);
}

void test_updateElem()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);
    Material* new_material = createMaterial("New Material", "New Supplier", 20, 2, 2, 2023);

    addElem(repo, material, 0);
    updateElem(repo, new_material, 0);

    // Assert statements to check if the material was updated correctly
    assert(equalMaterials(getElem_for_position(repo, 0), new_material));

    freeRepo(repo);
}

void test_checkExistance_repo()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    addElem(repo, material, 0);

    // Assert statement to check if the material exists in the repo
    assert(checkExistance_repo(repo, material) == 0);

    freeRepo(repo);
}

void test_availableMaterial()
{
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    // Assert statement to check if the material is available
    assert(availableMaterial(material, 1, 1, 2022) == 1);

    freeMaterial(material);
}

void test_equalMaterials()
{
    Material* material1 = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);
    Material* material2 = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    // Assert statement to check if the materials are equal
    assert(equalMaterials(material1, material2) == 1);

    freeMaterial(material1);
    freeMaterial(material2);
}

void test_material_for_a_supplier()
{
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    // Assert statement to check if the material is for the specified supplier
    assert(material_for_a_supplier(material, "Test Supplier") == 1);

    freeMaterial(material);
}

void test_printMaterial()
{
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    // Redirect stdout to a file
    freopen("output.txt", "w", stdout);

    // Call the printMaterial function
    printMaterial(material);

    // Close the file
    fclose(stdout);

    // Open the file in read mode
    FILE* file = fopen("output.txt", "r");

    // Assert statement to check if the material was printed correctly
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    assert(strcmp(buffer, "Name: Test Material, Supplier: Test Supplier, Quantity: 10, Expiration date -> Day: 1, Month: 1, Year: 2022\n") == 0);

    fclose(file);

    freeMaterial(material);
}

void test_addMaterial_services()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    addMaterial_services(services, material);

    // Assert statements to check if the material was added correctly
    assert(getLen(getRepo(services)) == 1);
    assert(equalMaterials(getElem_for_position(getRepo(services), 0), material));

    freeServices(services);
}

void test_updateMaterial_services()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);
    Material* new_material = createMaterial("New Material", "New Supplier", 20, 2, 2, 2023);

    addMaterial_services(services, material);
    updateMaterial_services(services, material, new_material);

    // Assert statements to check if the material was updated correctly
    assert(equalMaterials(getElem_for_position(getRepo(services), 0), new_material));

    freeServices(services);
}

void test_deleteMaterial_services()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);
    Material* material = createMaterial("Test Material", "Test Supplier", 10, 1, 1, 2022);

    addMaterial_services(services, material);
    deleteMaterial_services(services, material);

    // Assert statements to check if the material was deleted correctly
    assert(getLen(getRepo(services)) == 0);

    freeServices(services);
}

void test_seeNOAvailableMaterialsString()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);
    Material* material1 = createMaterial("Test Material 1", "Test Supplier", 10, 1, 1, 2022);
    Material* material2 = createMaterial("Test Material 2", "Test Supplier", 10, 1, 1, 2023);
    Material* material3 = createMaterial("Test Material 3", "Test Supplier", 10, 1, 1, 2024);

    addMaterial_services(services, material1);
    addMaterial_services(services, material2);
    addMaterial_services(services, material3);

    // Redirect stdout to a file
    freopen("output.txt", "w", stdout);

    // Call the seeNOAvailableMaterialsString function
    seeNOAvailableMaterialsString(services, 1, 1, 2023, "N");

    // Close the file
    fclose(stdout);

    // Open the file in read mode
    FILE* file = fopen("output.txt", "r");

    // Assert statement to check if the materials were printed correctly
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    assert(strcmp(buffer, "Name: Test Material 2, Supplier: Test Supplier, Quantity: 10, Expiration date -> Day: 1, Month: 1, Year: 2023\n") == 0);

    fclose(file);

    freeServices(services);
}

void test_seeMaterialsforSupplierLessthanQuantity()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);
    Material* material1 = createMaterial("Test Material 1", "Test Supplier", 10, 1, 1, 2022);
    Material* material2 = createMaterial("Test Material 2", "Test Supplier", 20, 1, 1, 2022);
    Material* material3 = createMaterial("Test Material 3", "Test Supplier", 30, 1, 1, 2022);

    addMaterial_services(services, material1);
    addMaterial_services(services, material2);
    addMaterial_services(services, material3);

    // Redirect stdout to a file
    freopen("output.txt", "w", stdout);

    // Call the seeMaterialsforSupplierLessthanQuantity function
    seeMaterialsforSupplierLessthanQuantity(services, "Test Supplier", 25);

    // Close the file
    fclose(stdout);

    // Open the file in read mode
    FILE* file = fopen("output.txt", "r");

    // Assert statement to check if the materials were printed correctly
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    assert(strcmp(buffer, "Name: Test Material 1, Supplier: Test Supplier, Quantity: 10, Expiration date -> Day: 1, Month: 1, Year: 2022\n") == 0);

    fclose(file);

    freeServices(services);
}

void test_generateMaterials()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);

    generateMaterials(services);

    // Assert statement to check if the materials were generated correctly
    assert(getLen(getRepo(services)) == 10);

    freeServices(services);
}

void test_seeAllMaterials()
{
    Repo* repo = createRepo(10, &freeMaterial);
    Services* services = createServices(repo);
    Material* material1 = createMaterial("Test Material 1", "Test Supplier", 10, 1, 1, 2022);
    Material* material2 = createMaterial("Test Material 2", "Test Supplier", 20, 1, 1, 2022);
    Material* material3 = createMaterial("Test Material 3", "Test Supplier", 30, 1, 1, 2022);

    addMaterial_services(services, material1);
    addMaterial_services(services, material2);
    addMaterial_services(services, material3);

    // Redirect stdout to a file
    freopen("output.txt", "w", stdout);

    // Call the seeAllMaterials function
    seeAllMaterials(services);

    // Close the file
    fclose(stdout);

    // Open the file in read mode
    FILE* file = fopen("output.txt", "r");

    // Assert statement to check if the materials were printed correctly
    char buffer[100];
    fgets(buffer, sizeof(buffer), file);
    assert(strcmp(buffer, "Name: Test Material 1, Supplier: Test Supplier, Quantity: 10, Expiration date -> Day: 1, Month: 1, Year: 2022\n") == 0);

    fclose(file);

    freeServices(services);
}

void run_tests()
{
    test_createMaterial();
    test_freeMaterial();
    test_createRepo();
    test_freeRepo();
    //test_addElem();
    test_deleteElem();
    test_updateElem();
    test_checkExistance_repo();
    test_availableMaterial();
    test_equalMaterials();
    test_material_for_a_supplier();
    test_printMaterial();
    test_addMaterial_services();
    test_updateMaterial_services();
    test_deleteMaterial_services();
    test_seeNOAvailableMaterialsString();
    test_seeMaterialsforSupplierLessthanQuantity();
    test_generateMaterials();
    test_seeAllMaterials();
}

int main()
{
    run_tests();

    return 0;
}