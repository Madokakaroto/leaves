#pragma once

namespace leaves {
	namespace math
	{
		template <typename T, size_type RowSize, size_type ColSize, typename M>
		struct matrix_layout;

		template <typename T, size_type RowSize, size_type ColSize>
		struct matrix_layout<T, RowSize, ColSize, row_major>
		{
			typedef T value_type;
			typedef value_type& reference;
			typedef value_type const_reference;
			typedef row_major major_order;
			static size_type const row_size = RowSize;
			static size_type const col_size = ColSize;

			typedef value_type array_type[row_size][col_size];

			reference operator(size_type row, size_type col)
			{
				return data_[row][col];
			}

			const_reference operator(size_type row, size_type col) const
			{
				return data_[row][col];
			}

			template <size_type RowIndex, size_type ColIndex>
			reference get()
			{
				return data_[RowIndex][ColIndex];
			}

			template <size_type RowIndex, size_type ColIndex>
			const_reference get() const
			{
				return data_[RowIndex][ColIndex];
			}

			template <size_type Index>
			reference get()
			{
				constexpr auto row_index = Index / row_size;
				constexpr auto col_index = Index % row_size;
				return data_[row_index][col_index];
			}

			template <size_type Index>
			const_reference get() const
			{
				constexpr auto row_index = Index / row_size;
				constexpr auto col_index = Index % row_size;
				return data_[row_index][col_index];
			}

			value_type const* data() const
			{
				return std::addressof(data_);
			}

			array_type data_;
		};

		template <typename T, size_type RowSize, size_type ColSize>
		struct matrix_layout<T, RowSize, ColSize, col_major>
		{
			typedef matrix_layout<T, RowSize, ColSize, col_major> this_type;
			typedef T value_type;
			typedef value_type& reference;
			typedef value_type const_reference;
			typedef col_major major_order;
			static size_type const row_size = RowSize;
			static size_type const col_size = ColSize;

			typedef value_type array_type[col_size][row_size];

			reference operator(size_type row, size_type col)
			{
				return data_[col][row];
			}

			const_reference operator(size_type row, size_type col) const
			{
				return data_[col][row];
			}

			template <size_type RowIndex, size_type ColIndex>
			reference get()
			{
				return data_[ColIndex][RowIndex];
			}

			template <size_type RowIndex, size_type ColIndex>
			const_reference get() const
			{
				return data_[ColIndex][RowIndex];
			}

			template <size_type Index>
			reference get()
			{
				constexpr auto col_index = Index / col_size;
				constexpr auto row_index = Index % col_size;
				return data_[col_index][row_index];
			}

			template <size_type Index>
			const_reference get() const
			{
				constexpr auto col_index = Index / col_size;
				constexpr auto row_index = Index % col_size;
				return data_[col_index][row_index];
			}

			value_type const* data() const
			{
				return std::addressof(data_);
			}

			array_type data_;
		};
	}
}