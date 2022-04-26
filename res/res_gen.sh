#!/usr/bin/env bash
#
#

res_dir=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
constellations_dir=$res_dir/constellations
template_path=$res_dir/template
help_path=$res_dir/help

parse_json(){

# hashmap key
echo -n '{"'
echo -n $(echo $(basename $1) | sed s/\.json//g)
echo -n '",'

# hashmap value
echo -n 'R"('
cat $1 | tr -d '()'
echo ')"},'

}

cat $src_head <<EOF
#ifndef CONSTELLATIONS_LIST_H_
#define CONSTELLATIONS_LIST_H_
#include <string>
#include <unordered_map>
EOF
cat $help_message_head <<EOF
inline const std::string res_help_message = R"(
EOF
cat $help_path
cat $help_message_tail <<EOF
)";
EOF
cat $template_head <<EOF
inline std::string res_template = R"(
EOF
cat $template_path
cat $template_tail <<EOF
)";
EOF
cat $constellations_json_list_head <<EOF
inline std::unordered_map<std::string, std::string> res_constellations_json_list{
EOF

for file in $constellations_dir/*.json;do
       parse_json $file
done

cat $constellations_json_list_head <<EOF
};
EOF
cat $src_tail <<EOF
#endif// CONSTELLATIONS_LIST_H_
EOF


