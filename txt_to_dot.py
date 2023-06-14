def convert_txt_to_dot(txt_file, dot_file):
    with open(txt_file, 'r') as f:
        txt_data = f.read()

    dot_data = "graph G{\n"
    rows = txt_data.split("\n")
    for i, row in enumerate(rows):
        values = row.split(",")
        joined_values = "--".join(values)
        dot_data += "{}{}".format(joined_values.replace(",", ";\n"), "" if i == len(rows) - 1 else ";\n")
    dot_data += "}"
    with open(dot_file, 'w') as f:
        f.write(dot_data)

    print("Conversion completed successfully.")

convert_txt_to_dot('./files/output_grafo.txt', './files/output.dot')
