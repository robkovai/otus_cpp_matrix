#pragma once

#include <map>
#include <array>
#include <utility>

template <typename T, T DefaultValue, std::size_t N = 2>
class Matrix {
    using Dimension = std::array<std::size_t, N>;
    using Values = std::map<Dimension, T>;
    using ValueIterator = typename Values::iterator;

    Values values;

    struct MatrixValue {
        MatrixValue(Matrix &matrix, Dimension dimension): matrix(matrix), dimension(dimension) {}

        operator T() const {
            return matrix.getValue(dimension);
        }

        auto operator=(const T &value) {
            return matrix.setValue(dimension, value);
        }
    private:
        Matrix &matrix;
        Dimension dimension;
    };

    struct MatrixIterator {
        MatrixIterator(ValueIterator iterator): iterator(iterator) {}

        auto operator*() {
            return std::make_pair(iterator->first, iterator->second);
        }

        MatrixIterator& operator++() {
            ++iterator;
            return *this;
        }

        friend bool operator!=(const MatrixIterator &lhs, const MatrixIterator &rhs) {
            return lhs.iterator != rhs.iterator;
        }
    private:
        ValueIterator iterator;
    };

public:
    Matrix() = default;

    std::size_t size() const {
        return this->values.size();
    }

    MatrixIterator begin() {
        return MatrixIterator(values.begin());
    }

    MatrixIterator end() {
        return MatrixIterator(values.end());
    }

    template<typename ... Args>
    MatrixValue operator()(Args ... args) {
        return MatrixValue(*this, {{ std::size_t(args)... }});
    }

private:
    const T getValue(Dimension dimension) const {
        auto i = this->values.find(dimension);
        return i != this->values.cend() ? i->second : DefaultValue;
    }

    T setValue(Dimension dimension, const T &value) {
        if (value == DefaultValue) {
            auto i = this->values.find(dimension);
            if (i != this->values.end())
                this->values.erase(i);
        } else
            this->values[dimension] = value;
        return value;
    }
};
