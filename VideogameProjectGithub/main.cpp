/*
Description: DFS of a graph implemented on resident evil
Input: mapFile and enemiesFile
Output: Location and order
*/
#include<iostream>
#include<vector>
#include<string>
#include<unordered_map>
#include<fstream>
#include<list>


bool saveAshley(std::string leon, int ammo,
    std::unordered_map<std::string, std::list<std::string>> map,
    std::unordered_map<std::string, int> enemiesAtLocation,
    std::unordered_map<std::string, int>& ammoAtLocation,
    std::unordered_map<std::string, std::string>& predecessor);

int main()
{
    std::unordered_map<std::string, std::list<std::string>> adjList;
    std::unordered_map<std::string, int> enemiesAtLocation;
    std::unordered_map<std::string, int> ammoAtLocation;
    std::unordered_map<std::string, std::string> predecessor;
    std::string mapFile, enemiesFile;
    std::string from, to;

    std::cout << "\nLEON!!!\n";
    std::cout << "\nEnter map file: ";
    std::cin >> mapFile;
    std::cout << "\nEnter enemies file: ";
    std::cin >> enemiesFile;

    std::ifstream mapStream(mapFile);
    std::ifstream enemiesStream(enemiesFile);

    while (mapStream >> from>> to)
        adjList[from].push_back(to);
    
    std::string location;
    int amount;
    while (enemiesStream >> location >> amount) {
        enemiesAtLocation[location] = amount;
        ammoAtLocation[location] = -1;
    }

    std::string start = "Village";
    bool ret = saveAshley(start, 10, adjList, enemiesAtLocation, ammoAtLocation, predecessor);
    if (ret) {
        std::cout << "\nI'm coming Ashley!\n";
        std::cout << start;
        while (predecessor.find(start) != predecessor.end()) {
            start = predecessor[start];
            std::cout << " -> " << start;
        }
        std::cout << "\n";
    } else {
        std::cout << "\nNot Found!\n";
    }
}
/*
 * saveAshley recursive function
 * @param map, leon, ammo, enemies at location, ammo at location, predecessor
 * @return bool - true if leon is at church
 * Description of algorithm: This function is called recursively until leon == "Church" which implies a path is then found (you would
return true in this case), the ammoAtLocation is your ”visited” array but this is not a boolean array/map
thus a node can be visited multiple times if any later visits occur that results in more ammo at arrival.
A false is returned whenever you reach a dead end or no paths from the current node lead to a success
etc. Initially when the function is called in main, you pass "Village" to the leon parameter, 10 into the
ammo parameter and then the rest of the maps you would declare in main. Once the function is finished,
you use the predecessor array to construct the path.
*/
bool saveAshley(std::string leon, int ammo,
    std::unordered_map<std::string, std::list<std::string>> map,
    std::unordered_map<std::string, int> enemiesAtLocation,
    std::unordered_map<std::string, int>& ammoAtLocation,
    std::unordered_map<std::string, std::string>& predecessor)
{
    if (leon == "Church")
        return true;
    for (auto neighbor: map[leon])
    {
        int a = ammo - enemiesAtLocation[neighbor];
        if (a > ammoAtLocation[neighbor]) {
            ammoAtLocation[neighbor] = a;
            predecessor[leon] = neighbor;
            if (saveAshley(neighbor, ammo-enemiesAtLocation[neighbor], map, enemiesAtLocation, ammoAtLocation, predecessor))
                return true;
        }
    }
    return false;
}
