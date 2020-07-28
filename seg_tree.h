#pragma once
#include <vector>
#include <functional>
#include <algorithm>
#include <iostream>
#include <cmath>

namespace segment_tree
{
    template<typename T>
    class segTree {

        using Func = std::function<T(const T& a, const T& b)>;

        public:
            segTree(const std::vector<T>& values, const Func& func) : func(func) {
                
                // tree construction
                n = values.size();

                tree.assign(2 * (int)std::pow(2, (int)std::ceil(std::log2(n))) - 1, 0);
                treeConstruction(values, 0, 0, n - 1);

            }

            T query(int min, int max) {
                if (min < 0 || max >= n || min > max) {
                    throw "index out of range";
                }

                return queryHelper(0, 0, n - 1, min, max);
            }

        protected:
            std::vector<T> tree;
            Func func;
            int n;

            void treeConstruction(const std::vector<T>& values, int cur, int left, int right) {
                int mid = getMidIdx(left, right);

                if (left == right) {
                    tree[cur] = values[left];
                    return;
                }

                treeConstruction(values, 2 * cur + 1, left, mid);
                treeConstruction(values, 2 * cur + 2, mid + 1, right);

                tree[cur] = func(tree[2 * cur + 1], tree[2 * cur + 2]);
            }

            T queryHelper(int cur, int left, int right, int qleft, int qright) {
                int mid = getMidIdx(left, right);

                if (qleft <= left && qright >= right)
                    return tree[cur];

                if (right < qleft || left > qright)
                    return INT_MAX;
                
                return func(queryHelper(2 * cur + 1, left, mid, qleft, qright),
                    queryHelper(2 * cur + 2, mid + 1, right, qleft, qright));
            }

            int getMidIdx(int l, int r) {
                return l + (r - l) / 2;
            }
    };
}