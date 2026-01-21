#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>

// وظائف مشتركة
void create_file(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file) {
        printf("File '%s' created successfully.\n", filename);
        fclose(file);
    } else {
        perror("Failed to create file");
    }
}

void delete_file(const char *filename) {
    if (remove(filename) == 0) {
        printf("File '%s' deleted successfully.\n", filename);
    } else {
        perror("Failed to delete file");
    }
}

void create_folder(const char *foldername) {
    if (mkdir(foldername, 0755) == 0) {
        printf("Folder '%s' created successfully.\n", foldername);
    } else {
        perror("Failed to create folder");
    }
}

void delete_folder(const char *foldername) {
    if (rmdir(foldername) == 0) {
        printf("Folder '%s' deleted successfully.\n", foldername);
    } else {
        perror("Failed to delete folder");
    }
}

void copy_file(const char *source, const char *destination) {
    FILE *src = fopen(source, "r");
    FILE *dest = fopen(destination, "w");
    char buffer[256];

    if (!src || !dest) {
        perror("File error");
        return;
    }

    while (fgets(buffer, sizeof(buffer), src)) {
        fputs(buffer, dest);
    }

    fclose(src);
    fclose(dest);
    printf("File copied from %s to %s\n", source, destination);
}

void create_symlink(const char *target, const char *linkpath) {
    if (symlink(target, linkpath) == 0) {
        printf("Symbolic link '%s' created for target '%s'.\n", linkpath, target);
    } else {
        perror("Failed to create symbolic link");
    }
}

// وظائف خاصة بـ Admin
void change_permissions(const char *filename, mode_t mode) {
    if (chmod(filename, mode) == 0) {
        printf("[Admin] Permissions changed successfully for %s to %o\n", filename, mode);
    } else {
        perror("[Admin] Failed to change permissions");
    }
}

// *New Function to Move a File*
void move_file(const char *source, const char *destination) {
    if (rename(source, destination) == 0) {
        printf("File '%s' moved to '%s'.\n", source, destination);
    } else {
        perror("Failed to move file");
    }
}

// وظائف خاصة بـ Moderator
void search_file(const char *filename, const char *keyword) {
    char command[256];
    snprintf(command, sizeof(command), "grep '%s' %s", keyword, filename);
    printf("[Moderator] Searching for '%s' in %s:\n", keyword, filename);
    system(command);
}

// وظائف خاصة بـ Player
void update_file(const char *filename) {
    FILE *file = fopen(filename, "a");
    if (!file) {
        perror("[Player] Unable to open file for updating");
        return;
    }

    char data[256];
    printf("[Player] Enter data to append to %s: ", filename);
    getchar(); // تنظيف الإدخال
    fgets(data, sizeof(data), stdin);
    fprintf(file, "%s", data);
    fclose(file);
    printf("[Player] File '%s' updated successfully.\n", filename);
}

// عرض محتوى الملفات
void display_file(const char *filename) {
    char command[256];
    snprintf(command, sizeof(command), "cat %s", filename);
    printf("Displaying content of %s:\n", filename);
    system(command);
}

// برنامج التشغيل الرئيسي
int main() {
    int choice, user_type;
    char filename[256], foldername[256], source[256], destination[256], target[256], linkpath[256];
    unsigned int permissions;
    char keyword[50];

    while (1) { // حلقة رئيسية
        printf("\nChoose user type:\n");
        printf("1. Admin\n");
        printf("2. Moderator\n");
        printf("3. Player\n");
        printf("0. Exit Program\n");
        printf("Enter your choice: ");
        scanf("%d", &user_type);

        if (user_type == 0) {
            printf("Exiting program. Goodbye!\n");
            break; // إنهاء البرنامج
        }

        while (1) { // حلقة فرعية لكل نوع مستخدم
            printf("\nChoose an operation:\n");
            switch (user_type) {
                case 1: // Admin
                    printf("1. Change file permissions\n");
                    printf("2. Create a file\n");
                    printf("3. Delete a file\n");
                    printf("4. Create a folder\n");
                    printf("5. Delete a folder\n");
                    printf("6. Copy a file\n");
                    printf("7. Create a symbolic link\n");
                    printf("8. Move a file\n"); // New option
                    break;

                case 2: // Moderator
                    printf("1. Search in a file\n");
                    printf("2. Display file content\n");
                    break;

                case 3: // Player
                    printf("1. Update a file\n");
                    printf("2. Display file content\n");
                    break;

                default:
                    printf("Invalid user type.\n");
                    return 1;
            }

            printf("0. Back to Main Menu\n");
            printf("Enter your choice: ");
            scanf("%d", &choice);

            if (choice == 0) {
                break; // الرجوع إلى القائمة الرئيسية
            }

            switch (choice) {
                case 1:
                    if (user_type == 1) {
                        printf("Enter the file name: ");
                        scanf("%s", filename);
                        printf("Enter the permissions in octal (e.g., 0755): ");
                        scanf("%o", &permissions);
                        change_permissions(filename, (mode_t)permissions);
                    } else if (user_type == 2) {
                        printf("Enter the file name: ");
                        scanf("%s", filename);
                        printf("Enter the keyword to search: ");
                        scanf("%s", keyword);
                        search_file(filename, keyword);
                    } else if (user_type == 3) {
                        printf("Enter the file name to update: ");
                        scanf("%s", filename);
                        update_file(filename);
                    }
                    break;

                case 2:
                    if (user_type == 1) {
                        printf("Enter the file name to create: ");
                        scanf("%s", filename);
                        create_file(filename);
                    } else {
                        printf("Enter the file name to display: ");
                        scanf("%s", filename);
                        display_file(filename);
                    }
                    break;

                case 3:
                    if (user_type == 1) {
                        printf("Enter the file name to delete: ");
                        scanf("%s", filename);
                        delete_file(filename);
                    }
                    break;

                case 4:
                    if (user_type == 1) {
                        printf("Enter the folder name to create: ");
                        scanf("%s", foldername);
                        create_folder(foldername);
                    }
                    break;

                case 5:
                    if (user_type == 1) {
                        printf("Enter the folder name to delete: ");
                        scanf("%s", foldername);
                        delete_folder(foldername);
                    }
                    break;

                case 6:
                    if (user_type == 1) {
                        printf("Enter the source file name: ");
                        scanf("%s", source);
                        printf("Enter the destination file name: ");
                        scanf("%s", destination);
                        copy_file(source, destination);
                    }
                    break;

                case 7:
                    if (user_type == 1) {
                        printf("Enter the target file: ");
                        scanf("%s", target);
                        printf("Enter the link path: ");
                        scanf("%s", linkpath);
                        create_symlink(target, linkpath);
                    }
                    break;

                case 8: // Move file for Admin
                    if (user_type == 1) {
                        printf("Enter the source file name: ");
                        scanf("%s", source);
                        printf("Enter the destination file name: ");
                        scanf("%s", destination);
                        move_file(source, destination); // Call the move file function
                    }
                    break;

                default:
                    printf("Invalid choice.\n");
            }
        }
    }

    return 0;
}