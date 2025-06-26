#include <ranges>
#include <algorithm>
#include <functional>

template<class TData, class TView>
class TensorView {
    public:
        TensorView(TView& view) : 
            mSrcView(view)
        {
            mData.resize(view.size());
        }

        void CollectData() {
            auto data_view = mData.begin();
            std::for_each(mSrcView.begin(), mSrcView.end(), [&](auto& item) {
                *data_view++ = item;
            });
        }

        void StoreData() {
            auto data_view = mData.begin();
            std::for_each(mSrcView.begin(), mSrcView.end(), [&](auto& item) {
                item = *data_view++;
            });
        }

        std::vector<TData>& GetData() {
            return mData;
        }

    private:
        std::vector<TData> mData;

        TView mSrcView;
};
