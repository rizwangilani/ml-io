#include <gtest/gtest.h>
#include <mlio.h>

namespace mlio {

TEST(foo, test)
{
    EXPECT_TRUE(true);
}

TEST(foo, foo_textline_Test)
{
    // gets a list of data_store here (list of data_store = dataset)
    auto dataset = mlio::list_files("/Users/sggilani/Documents/workplace/mlio/mlio/tests/mlio-test/data/text",
        /*pattern=*/"*.txt");

    // csv_reader supports an extensive set of constructor parameters.
    // Here we just specify the two required arguments.
    mlio::data_reader_params prm{dataset, 200};

    auto reader = mlio::make_intrusive<mlio::text_line_reader>(prm);

    // Read the dataset five times (five epochs).
    for (auto i = 0; i < /*num_epochs*/ 2; i++) {
        mlio::intrusive_ptr<mlio::example> exm;
        while ((exm = reader->read_example()) != nullptr) {
            // Get the ML-IO tensor of the column called 'value'.
            auto lbl = static_cast<dense_tensor *>(exm->find_feature("value").get());
            auto str_ptr = static_cast<std::string *>(lbl->data().data());
            std::cout<<*str_ptr++<<std::endl;
            std::cout<<*str_ptr++<<std::endl;
            std::cout<<*str_ptr<<std::endl;
            // Zero-copy convert it to DLPack.
            //DLManagedTensor *dl = mlio::as_dlpack(*lbl);
        }
        reader->reset();
    }
}
}  // namespace mlio
