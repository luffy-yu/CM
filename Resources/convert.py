import os
from lxml import etree

line_template = 'L"{name}", make_pair<wstring, wstring>(L"{value}", L"{comment}")'

file_template = """#include <map>
#include "ResourceProvider.h"

std::map<wstring, pair<wstring, wstring>> rs_name_value_comment_map = {
%s
};

std::map<wstring, pair<wstring, wstring>> ce_name_value_comment_map = {
%s
};

wstring CalculationManager::GetResourceString(wstring input)
{
	auto found = rs_name_value_comment_map.find(input);
	if (found == rs_name_value_comment_map.end()) {
		return L"";
	}
	else {
		return found->second.first;
	}
}

wstring CalculationManager::GetCEngineString(wstring input)
{
	auto found = ce_name_value_comment_map.find(input);
	if (found == ce_name_value_comment_map.end()) {
		return L"";
	}
	else {
		return found->second.first;
	}
}

wstring GetString(wstring input)
{
	return CalculationManager::GetCEngineString(input);
}
"""


def to_list(filename):
    html = etree.parse(filename, etree.XMLPullParser())
    all_data = html.xpath('//data')
    res = []
    for data in all_data:
        d = {}
        name = data.attrib['name']
        d.update(dict(name=name))
        children = data.getchildren()
        for child in children:
            tag = child.tag
            value = child.text
            d.update({tag: value})
        value = d.get('value', '')
        value = value.replace('"', '\'').replace("\\", r"\\")
        d['value'] = value
        comment = d.get('comment', '')
        # update
        comment = comment.replace('"', '\'')
        d['comment'] = comment
        res.append(d)
    return res


folder = './en-US/'
ce_filename = 'CEngineStrings.resw'
rs_filename = 'Resources.resw'

rs_list = to_list(os.path.join(folder, rs_filename))
ce_list = to_list(os.path.join(folder, ce_filename))

format_list = lambda x: ',\n'.join(['\t{' + line_template.format(**one) + '}' for one in x])

ce = format_list(ce_list)
rs = format_list(rs_list)

file_content = file_template % (rs, ce)

output = r'E:\GitHub\CM\ResourceProvider.cpp'

with open(output, 'w', encoding='utf-8') as f:
    f.write(file_content)
