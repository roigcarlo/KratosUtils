#pragma once

#include <algorithm>
#include <functional>

#include <range/v3/view/any_view.hpp>
#include <range/v3/algorithm/for_each.hpp>

template<class TData>
class TensorView {
    public:
        using ViewType = ranges::any_view<TData&, ranges::category::input>;

        TensorView(ViewType view) : 
            mSrcView(view)
        {
            mData.resize(ranges::distance(view));
        }

        void CollectData() {
            auto data_view = mData.begin();
            ranges::for_each(mSrcView.begin(), mSrcView.end(), [&](auto& item) {
                *data_view++ = item;
            });
        }

        void StoreData() {
            auto data_view = mData.begin();
            ranges::for_each(mSrcView.begin(), mSrcView.end(), [&](auto& item) {
                item = *data_view++;
            });
        }

        std::vector<TData>& GetData() {
            return mData;
        }

    private:
        std::vector<TData> mData;

        ViewType mSrcView;
};
