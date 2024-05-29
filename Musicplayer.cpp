#include <iostream>
#include <fstream>
#include <queue>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <cstring> // For strcpy, strcmp
#include <climits> // For INT_MAX

using namespace std;

// Exception class for playlist operations
class PlaylistException : public exception {
public:
    const char* what() const throw() {
        return "Error in playlist operation";
    }
};

// Node structure for doubly linked list
struct node {
    char song[100];
    vector<struct node*> related_songs;  // List of related songs
    struct node *next;
    struct node *prev;
};


// Global variables
unordered_map<string, node*> playlists; // Map to hold multiple playlists
unordered_set<string> all_songs; // Set to track all songs across playlists
struct node *top = nullptr; // Global variable declaration
struct node *top1 = nullptr; // Additional global variable
struct node *temp = nullptr;


// Function prototypes
//void tofile(char a[]);
void tofile(const char a[]);



void add_node(struct node *first);
bool binary_search(struct node *start, char key[]);
void BFS(struct node *start);
//void DFS(struct node *start, char song[]);
//void dijkstra(struct node *start, char song[]);
void add_node_file(struct node *first, const string &a); // Updated prototype
//void delete_file(char a[]);
void delete_file(const char a[]);

void del_node(struct node *first);
void printlist(struct node *first);
void count_nodes(struct node *first);
struct node *del_pos(struct node *pointer, int pos);
void search1(struct node *first);
void create();
void push(char data[]);
void display();
void play(struct node *first);
void recent();
void topelement();
void sort(node *&pointer);
void addplaylist(struct node *start);
void delete_all_data_from_file();
void del_search(struct node *&start);
void update_play_count(char song[]);
void display_most_played_songs();
void topologicalSort(struct node *start);
// Function to write data to file
void tofile(const char a[]) {
    ofstream f1;
    f1.open("playlist.txt", ios::out | ios::app);
    if (!f1) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    f1 << a << endl;
    f1.close();
}

// Function to add a node to the end of the linked list
void add_node(struct node *first) {
    char a[100];
    while (first->next != NULL) {
        first = first->next;
    }

    first->next = new node;
    first->next->prev = first;
    first = first->next;

    cout << "\nEnter Song name: ";
    cin >> a; // Using cin for input

    // Check if the song already exists in the playlist
    struct node *temp = first->prev; // Start from the previous node

    while (temp != NULL) {
        if (strcmp(temp->song, a) == 0) {
            cout << "Song already exists in the playlist. Cannot add a duplicate song." << endl;
            return;
        }
        temp = temp->prev;
    }

    if (first == nullptr) {
        cerr << "Error: Invalid playlist node encountered!" << endl;
        return;
    }

    strcpy(first->song, a);
    first->next = NULL;

    cout << "Song added successfully." << endl;
}

// Function to write a song to file
void add_song_to_file(const char a[]) {
    ofstream f1;
    f1.open("playlist.txt", ios::out | ios::app);
    if (!f1) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }
    f1 << a << endl;
    f1.close();
    cout << "Song added successfully to File." << endl;
}

// Binary search algorithm
bool binary_search(struct node *start, char key[]) {
    int left = 0, right = 0, mid = 0;
    struct node *temp = start;

    // Counting the total number of nodes
    while (temp->next != NULL) {
        temp = temp->next;
        right++;
    }
    right++;

    while (left <= right) {
        mid = (left + right) / 2;
        temp = start;
        for (int i = 0; i < mid; i++)
            temp = temp->next;
        int compare = strcmp(temp->song, key);
        if (compare == 0)
            return true;
        else if (compare < 0)
            left = mid + 1;
        else
            right = mid - 1;
    }
    return false;
}

// Breadth-first search algorithm
void BFS(struct node *start) {
    if (start == NULL)
        return;

    queue<struct node *> q;
    struct node *temp = start;
    q.push(temp);

    while (!q.empty()) {
        temp = q.front();
        q.pop();
        cout << temp->song << endl;

        if (temp->next != NULL)
            q.push(temp->next);
    }
}
// Function to add a node to the end of the linked list from a file
void add_node_file(struct node *first, const string &a) {
    while (first->next != NULL) {
        first = first->next;
    }
    first->next = new node;
    first->next->prev = first;
    first = first->next;
    strcpy(first->song, a.c_str());
    first->next = NULL;
}



// Function to delete a line from file
// Function to delete a line from file
void delete_file(const char a[]) {
    ifstream f1("playlist.txt");
    ofstream f2("temp.txt");
    string line;
    int x = 0;

    if (!f1.is_open() || !f2.is_open()) {
        cerr << "Error: Unable to open file." << endl;
        return;
    }

    while (getline(f1, line)) {
        if (strcmp(a, line.c_str()) != 0) {
            f2 << line << endl;
        } else {
            x = 1;
        }
    }

    f1.close();
    f2.close();

    if (remove("playlist.txt") != 0) {
        perror("Error deleting original file");
        return;
    }
    if (rename("temp.txt", "playlist.txt") != 0) {
        perror("Error renaming temporary file");
        return;
    }

    if (x == 0) {
        cout << "\n#Song Not found" << endl;
    } else {
        cout << "\nSong has been deleted." << endl;
    }
}



// Function to delete node from end
void del_node(struct node *first) {
    while ((first->next)->next != NULL) {
        first = first->next;
    }
    struct node *temp;
    temp = (first->next)->next;

    first->next = NULL;

    delete temp;
    cout << "Deleted" << endl;
}

// Function to print the linked list
void printlist(struct node *first) {
    cout << "\nPlaylist Name- ";
    while (first->next != NULL) {
        cout << first->song << endl;
        first = first->next;
    }
    cout << first->song << endl;
}

// Function to count nodes in linked list
// Function to count nodes in linked list, excluding the playlist name
void count_nodes(struct node *first) {
    int i = 0;
    // Skip the playlist name node
    first = first->next;
    while (first != NULL) {
        first = first->next;
        i++;
    }
    cout << "\nTotal songs: " << i << endl;
}


// Function to delete a node at a given position
struct node *del_pos(struct node *start, int pos) {
    struct node *temp = start;
    struct node *prev = nullptr;

    // If list is empty
    if (temp == nullptr) {
        cout << "List is empty" << endl;
        return nullptr;
    }

    // Delete head node
    if (pos == 1) {
        start = temp->next;
        if (start != nullptr)
            start->prev = nullptr;
        delete temp;
        cout << "Deleted" << endl;
        return start;
    }

    // Traverse to the position to be deleted
    for (int i = 1; temp != nullptr && i < pos; i++) {
        prev = temp;
        temp = temp->next;
    }

    // If position is more than number of nodes
    if (temp == nullptr) {
        cout << "Position exceeds the number of nodes" << endl;
        return start;
    }

    // Unlink the node from the linked list
    prev->next = temp->next;
    if (temp->next != nullptr)
        temp->next->prev = prev;

    // Delete the node from memory
    delete temp;
    cout << "Deleted" << endl;

    return start;
}


// Function to search for a song in the playlist
void search1(struct node *first) {
    char song[100];
    cout << "\nEnter song To be Searched- ";
    cin >> song;  // Using cin instead of scanf
    int flag = 0;

    // Traverse from the actual song nodes, not the playlist node
    first = first->next;

    while (first != NULL) {
        if (strcmp(first->song, song) == 0) {
            cout << "\n#Song Found" << endl;
            flag++;
            break;
        } else {
            first = first->next;
        }
    }
    if (flag == 0) {
        cout << "\n#Song Not found" << endl;
    }
}


// Function to initialize the linked list
void create() {
    top = NULL;
}

// Function to push a song to the recently played list
void push(char data[]) {
    if (top == NULL) {
        top = new node;
        top->next = NULL;
        strcpy(top->song, data);
    } else if (strcmp(top->song, data) != 0) {
        temp = new node;
        temp->next = top;
        strcpy(temp->song, data);
        top = temp;
    }

    // Ensure the stack size does not grow beyond a certain limit
    node *current = top;
    int count = 1;
    while (current->next != NULL && count < 5) {
        current = current->next;
        count++;
    }
    if (current->next != NULL) {
        node *toDelete = current->next;
        current->next = NULL;
        delete toDelete; // Properly delete the extra node
    }
}

// Function to display recently played songs
void display() {
    top1 = top;
    if (top1 == NULL) {
        printf("\n=>NO recently played tracks.\n");
        return;
    }
    printf("\n=>Recently played tracks-\n");
    while (top1 != NULL) {
        printf("%s", top1->song);
        printf("\n");
        top1 = top1->next;
    }
}

// Maintain a dynamic list of recently played songs
vector<string> recentlyPlayed;

void push_recently_played(char data[]) {
    // Ensure song is not already in the list
    auto it = find(recentlyPlayed.begin(), recentlyPlayed.end(), data);
    if (it != recentlyPlayed.end()) {
        recentlyPlayed.erase(it);
    }

    // Add song to recently played list
    recentlyPlayed.push_back(data);

    // Limit list to 5 most recent songs
    if (recentlyPlayed.size() > 5) {
        recentlyPlayed.erase(recentlyPlayed.begin());
    }
}

void display_recently_played() {
    cout << "\n=>Recently played tracks-" << endl;
    for (const auto &song : recentlyPlayed) {
        cout << song << endl;
    }
}
// Dynamic programming table to store most played songs
unordered_map<string, int> playCount;

void update_play_count(char song[]) {
    string key(song);
    playCount[key]++;
}

void display_most_played_songs() {
    cout << "\nMost played songs:" << endl;
    vector<pair<string, int>> sortedSongs;
    for (const auto &entry : playCount) {
        sortedSongs.push_back({entry.first, entry.second});
    }
    sort(sortedSongs.begin(), sortedSongs.end(), [](const pair<string, int> &a, const pair<string, int> &b) {
        return a.second > b.second;
    });

    for (const auto &song : sortedSongs) {
        cout << song.first << " - " << song.second << " plays" << endl;
    }
}


// Function to play a song
void play(struct node *first) {
    char song[100];
    printlist(first);
    cout << "\nChoose song you wish to play- ";
    cin >> song;
    int flag = 0;

    // Use a temporary pointer to traverse without affecting the original pointer
    struct node *current = first;

    while (current != NULL) {
        if (strcmp(current->song, song) == 0) {
            cout << "\n=>Now Playing......" << song << endl;
            flag++;
            push(song);
            update_play_count(song);  // Update play count for the song
            break;
        } else {
            current = current->next;
        }
    }
    if (flag == 0) {
        cout << "\n#Song Not found" << endl;
    }
}


// Function to display the recently played list
void recent() {
    display();
}

// Function to display the last played song
void topelement() {
    top1 = top;
    if (top1 == NULL) {
        printf("\n#NO last played tracks.\n");
        return ;
    }
     cout << "\n=>Last Played Song - " << top->song << endl;
}

// Function to sort playlist alphabetically
void sort(node *&pointer) {
    struct node *current = pointer, *index = nullptr;
    char temp[100];

    if (pointer == nullptr) {
        return;
    } else {
        while (current != nullptr) {
            index = current->next;

            while (index != nullptr) {
                if (strcmp(current->song, index->song) > 0) {
                    strcpy(temp, current->song);
                    strcpy(current->song, index->song);
                    strcpy(index->song, temp);
                }
                index = index->next;
            }
            current = current->next;
        }
    }
    cout << "\nSorted Playlist:" << endl;
    printlist(pointer);
}
// Topological Sort using DFS for sorting playlist
// Topological Sort using DFS
void topologicalSortUtil(struct node *v, unordered_map<struct node*, bool> &visited, stack<struct node *> &Stack) {
    visited[v] = true;

    // Recur for all the vertices adjacent to this vertex
    for (auto adj : v->related_songs) {
        if (!visited[adj]) {
            topologicalSortUtil(adj, visited, Stack);
        }
    }

    // Push current vertex to stack which stores result
    Stack.push(v);
}

void topologicalSort(struct node *start) {
    stack<struct node *> Stack;
    unordered_map<struct node*, bool> visited;

    // Mark all the vertices as not visited
    for (struct node *temp = start; temp != nullptr; temp = temp->related_songs.empty() ? nullptr : temp->related_songs[0]) {
        if (!visited[temp]) {
            topologicalSortUtil(temp, visited, Stack);
        }
    }

    // Print contents of stack
    cout << "\nSorted Playlist:" << endl;
    while (!Stack.empty()) {
        cout << Stack.top()->song << endl;
        Stack.pop();
    }
}




void addplaylist(struct node *start) {
    //struct node *start = nullptr; // Ensure this matches the expected type

    fstream f1;
    string line;
    f1.open("playlist.txt", ios::in);
    while (getline(f1, line)) {
        add_node_file(start, line);
    }
    f1.close();
}


void delete_all_data_from_file() {
    fstream f1;
    f1.open("playlist.txt", ios::out);
    f1 << "";
    f1.close();

    cout << "File deleted successfully" << endl;
}
void deletemenu(struct node *start) {
    cout << "\n1. Delete a specific song\n2. Delete the last song\n3. Delete song at a specific position\n";
    int choice;
    cin >> choice;
    switch (choice) {
        case 1:
            del_search(start);
            break;
        case 2:
            del_node(start);
            break;
        case 3:
            int pos;
            cout << "Enter position to delete: ";
            cin >> pos;
            start = del_pos(start, pos);
            break;
        default:
            cout << "Invalid choice" << endl;
            break;
    }
}



void del_search(struct node *&start) {
    char song[100];
    printlist(start);
    cout << "\nChoose song you wish to delete- ";
    cin >> song;
    int flag = 0;
    struct node *current = start;

    while (current != NULL) {
        if (strcmp(current->song, song) == 0) {
            cout << "\n#Song Found" << endl;

            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                // Deleting the head node
                start = current->next;
                if (start != NULL) {
                    start->prev = NULL;
                }
            }

            if (current->next != NULL) {
                current->next->prev = current->prev;
            }

            delete_file(current->song);
            delete current; // Use delete for C++ instead of free
            flag++;
            break;
        } else {
            current = current->next;
        }
    }

    if (flag == 0) {
        cout << "\n#Song Not found" << endl;
    } else {
        cout << "\nSong deleted successfully." << endl;
    }
}
void add_related_song(struct node *first, const char song[], const char related_song[]) {
    struct node *song_node = nullptr;
    struct node *related_node = nullptr;
    struct node *temp = first;

    // Find the song nodes
    while (temp != NULL) {
        if (strcmp(temp->song, song) == 0) {
            song_node = temp;
        }
        if (strcmp(temp->song, related_song) == 0) {
            related_node = temp;
        }
        temp = temp->next;
    }

    // Add the related song if both nodes are found
    if (song_node != NULL && related_node != NULL) {
        song_node->related_songs.push_back(related_node);
    } else {
        cout << "\n#One or both songs not found" << endl;
    }
}



int main() {
    try {
        int choice;
        struct node *start = nullptr;
        string current_playlist;
        node *hold = nullptr;

        cout << "\t\t\t*********WELCOME TO MUSIC PLAYER*********" << endl;
        cout << "\n**please use '_' for space." << endl;

        create();

      do {
    cout << "\n1. Create New Playlist\n2. Add New Song to Current Playlist\n3. Delete Song\n4. Display Entered Playlist\n5. Total Songs\n6. Search Song\n7. Play Song\n8. Recently Played List\n9. Last Played\n10. Sorted Playlist\n11. Add From File\n12. Delete All Data From File\n13. Switch Playlist\n";
    cout << "14. Display Most Played Songs\n15. Topological Sort\n16. Exit\n"; // Added new option here
    cout << "\nEnter your choice- ";
    cin >> choice;

            switch (choice) {
                case 1: {
                    cout << "\nEnter new playlist name: ";
                    cin.ignore();
                    getline(cin, current_playlist);
                    if (playlists.find(current_playlist) != playlists.end()) {
                        cout << "\nPlaylist already exists. Choose another name." << endl;
                        break;
                    }
                    start = new node;
                    strcpy(start->song, current_playlist.c_str());
                    start->next = nullptr;
                    start->prev = nullptr;
                    hold = start;
                    playlists[current_playlist] = start;
                    cout << "\nPlaylist created: " << current_playlist << endl;
                    break;
                }
                case 2:
                    if (current_playlist.empty()) {
                        cout << "\nNo playlist selected. Create or switch to a playlist first." << endl;
                        break;
                    }
                    add_node(playlists[current_playlist]);
                    // Add the following line to prompt the user to add the song to the file
                    char choice;
                    cout << "Do you want to add this song to the file? (y/n): ";
                    cin >> choice;
                    if (choice == 'y' || choice == 'Y') {
                        // Get the song name of the last added node
                        struct node *last = playlists[current_playlist];
                        while (last->next != NULL) {
                            last = last->next;
                        }
                        add_song_to_file(last->song);
                    }
                    break;
                     case 3:
                    deletemenu(start);
                    break;


                case 4:
                    printlist(hold);
                    break;
                case 5:
                    count_nodes(hold);
                    break;
                case 6:
                    search1(start);
                    break;
                case 7:
                    play(hold);
                    break;
                case 8:
                    recent();
                    break;
                case 9:
                    topelement();
                    break;
                case 10:
                    sort(start);
                    break;
                case 11:
                    addplaylist(start);
                    break;
                case 12:
                    delete_all_data_from_file();
                    break;
                case 13: {
                    string playlist_to_switch;
                    cout << "\nEnter playlist name to switch: ";
                    cin.ignore();
                    getline(cin, playlist_to_switch);
                    if (playlists.find(playlist_to_switch) == playlists.end()) {
                        cout << "\nPlaylist not found. Try again." << endl;
                        break;
                    }
                    current_playlist = playlist_to_switch;
                    start = playlists[current_playlist];
                    hold = start;
                    cout << "\nSwitched to playlist: " << current_playlist << endl;
                    break;
                }


                case 14:
                    display_most_played_songs();
                    break;
                case 15:
                    topologicalSort(start);
                    break;
                      case 16:
                    exit(0);
                    break;


                default:
                    cout << "Invalid choice" << endl;
                    break;
            }
        } while (choice != 14);

    } catch (const PlaylistException& e) {
        cerr << "Error: " << e.what() << endl;
    } catch (const exception& e) {
        cerr << "Exception: " << e.what() << endl;
    } catch (...) {
        cerr << "Unknown exception occurred" << endl;
    }
    return 0;
}
