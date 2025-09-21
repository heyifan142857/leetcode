//
// Created by user on 2025/9/21.
//
#include <bits/stdc++.h>
using namespace std;

class MovieRentingSystem {
    struct MovieEntry {
        int price, shop;
        bool operator<(const MovieEntry &o) const {
            if (price != o.price) return price < o.price;
            return shop < o.shop;
        }
    };

    struct RentedEntry {
        int price, shop, movie;
        bool operator<(const RentedEntry &o) const {
            if (price != o.price) return price < o.price;
            if (shop != o.shop) return shop < o.shop;
            return movie < o.movie;
        }
    };

    unordered_map<int, set<MovieEntry>> available;

    set<RentedEntry> rented;

    unordered_map<long long, int> priceMap;

    int n;

    long long key(int shop, int movie) {
        return ( (long long)shop << 32 ) | (unsigned int)movie;
    }

public:
    MovieRentingSystem(int n, vector<vector<int>>& entries): n(n) {
        for (auto &e : entries) {
            int shop = e[0], movie = e[1], price = e[2];
            available[movie].insert({price, shop});
            priceMap[key(shop, movie)] = price;
        }
    }

    vector<int> search(int movie) {
        vector<int> res;
        auto it = available.find(movie);
        if (it == available.end()) return res;
        int cnt = 0;
        for (auto &entry : it->second) {
            res.push_back(entry.shop);
            if (++cnt == 5) break;
        }
        return res;
    }

    void rent(int shop, int movie) {
        int price = priceMap[key(shop, movie)];
        available[movie].erase({price, shop});
        rented.insert({price, shop, movie});
    }

    void drop(int shop, int movie) {
        int price = priceMap[key(shop, movie)];
        rented.erase({price, shop, movie});
        available[movie].insert({price, shop});
    }

    vector<vector<int>> report() {
        vector<vector<int>> res;
        int cnt = 0;
        for (auto &entry : rented) {
            res.push_back({entry.shop, entry.movie});
            if (++cnt == 5) break;
        }
        return res;
    }
};


/**
 * Your MovieRentingSystem object will be instantiated and called as such:
 * MovieRentingSystem* obj = new MovieRentingSystem(n, entries);
 * vector<int> param_1 = obj->search(movie);
 * obj->rent(shop,movie);
 * obj->drop(shop,movie);
 * vector<vector<int>> param_4 = obj->report();
 */