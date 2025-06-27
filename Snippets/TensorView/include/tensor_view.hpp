#pragma once

#include <algorithm>
#include <functional>

#include <range/v3/view/any_view.hpp>
#include <range/v3/algorithm/for_each.hpp>

template<class TData>
class DataView {
    public:
        using ViewType = ranges::any_view<TData&, ranges::category::input>;

        DataView(ViewType view) 
            : mSrcView(view)
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

template<class TContainer, class TData>
class ContainerView : public std::enable_shared_from_this<ContainerView<TContainer, TData>> {
    public:
        using SelfType = ContainerView<TContainer, TData>;

        ContainerView(TContainer& container) 
            : mContainer(container)
            , mDataView(nullptr)
            {}

        template<class TNewData>
        std::shared_ptr<ContainerView<TContainer, TNewData>> FromThisView() const {
            return std::make_shared<ContainerView<TContainer, TNewData>>(mContainer);
        }

        template<class TIndexType, class TFunctor>
        std::shared_ptr<SelfType> CreateDataView(TIndexType index, TFunctor&& functor) {
            auto view = mContainer | ranges::views::transform(
                [index, functor](auto& item) -> TData& {
                    return functor(item, index);
                });

            mDataView = std::make_shared<DataView<TData>>(view);
            return this->shared_from_this();
        }

        std::shared_ptr<DataView<TData>> GetDataView() {
            return mDataView;
        }

    private:
        TContainer& mContainer;
        std::shared_ptr<DataView<TData>> mDataView;
};