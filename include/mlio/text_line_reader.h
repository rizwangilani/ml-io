#include "mlio/config.h"
#include "mlio/parallel_data_reader.h"

namespace mlio {
inline namespace v1 {

class MLIO_API text_line_reader final : public parallel_data_reader {
public:
    explicit text_line_reader(data_reader_params rdr_prm);

    text_line_reader(text_line_reader const &) = delete;

    text_line_reader(text_line_reader &&) = delete;

    ~text_line_reader() final;

public:
    text_line_reader &
    operator=(text_line_reader const &) = delete;

    text_line_reader &
    operator=(text_line_reader &&) = delete;

public:
    void
    reset() noexcept final;

private:
    intrusive_ptr<record_reader>
    make_record_reader(data_store const &ds) final;

    void
    infer_schema(instance const &ins) final;

    intrusive_ptr<example>
    decode(instance_batch const &batch) const final;

    intrusive_ptr<dense_tensor>
    make_tensor(std::vector<instance> const &instances,
                std::size_t batch_size) const;
};

}  // namespace v1
}  // namespace mlio
