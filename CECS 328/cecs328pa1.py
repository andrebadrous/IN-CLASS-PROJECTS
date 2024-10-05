
def isValidGrid(matrix):
    matrix_len = len(matrix)

    for row_num in range(matrix_len):
        rows = set()
        for column_num in range(matrix_len):
            rows.add(matrix[row_num][column_num])

        if len(rows) != matrix_len:
            return False

    for column_num in range(matrix_len):
        columns = set()
        for row_num in range(matrix_len):
            columns.add(matrix[row_num][column_num])

        if len(columns) != matrix_len:
            return False

    half_matrix = matrix_len/2
    q_len = (len(matrix) * len(matrix)) / 4
    q1 = set()
    q2 = set()
    q3 = set()
    q4 = set()
    for row_num in range(matrix_len):
        for column_num in range(matrix_len):
            if row_num < half_matrix:
                if column_num < half_matrix:
                    q1.add(matrix[row_num][column_num])
                else:
                    q3.add(matrix[row_num][column_num])
            else:
                if column_num < half_matrix:
                    q2.add(matrix[row_num][column_num])
                else:
                    q4.add(matrix[row_num][column_num])
    if (len(q1) != q_len) or (len(q2) != q_len) or (len(q3) != q_len) or (len(q4) != q_len):
        return False

    return True

