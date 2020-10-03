const repo_url = 'https://raw.githubusercontent.com/Dup4/TI1049-Code-Repo/master/2020%E7%89%9B%E5%AE%A2%E5%9B%BD%E5%BA%86%E9%9B%86%E8%AE%AD%E6%B4%BE%E5%AF%B9/day3/';
const practice_link = "https://ac.nowcoder.com/acm/contest/7830";
const problem_id = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J'];
const ac_status = [1, 1, 0, 0, 0, 1, 0, 0, 0, 1];
const problem_code_path = ["a/a.cpp", "b/b.cpp", "c/c.cpp", "d/d.cpp", "e/e.cpp", "f/f.cpp", "g/g.cpp", "h/h.cpp", "i/i4.cpp", "j/j.cpp"];
const problem_code_suffix = ["cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp", "cpp"];
const problem_name = [
    "Leftbest", 
    "First Date", 
    "Sequence",
    "Capture Stars", 
    "Triangulation", 
    "Points", 
    "ParallelNetworkAnalysis",
    "Graph",
    "Rooted Tree",
    "Flowers"
];
const ac_author = [
    "Dup4",
    "all",
    "-",
    "-",
    "-",
    "Dup4",
    "-",
    "-",
    "Dup4",
    "Dup4 & groggy_"
];
const ac_time = [
    "00:13(+)",
    "03:15(+)",
    "-",
    "-",
    "-",
    "00:06(+)",
    "-",
    "-",
    "-",
    "01:24(+6)"
];

const template = 
`
<details class = 'note'>
<summary>目录</summary>
<div>

[TOC]

</div>
</details>

# Contest Info

[Practice Link](${practice_link})

${generate_table(ac_status, problem_id)}

- O    在比赛中通过
- Ø    赛后通过
- !    尝试了但是失败了
- \\-   没有尝试

# Solutions


`;

function get(url) {
    return new Promise((resolve, reject) => {
        $.get(url, function(data, err) {
            resolve(data);
        })
    })
}

function generate_table(ac_status, problem_id) {
    const len = ac_status.length;
    var str = [
        "|Solved|",
        "|:-:|",
        `|${ac_status.reduce((a, b) => a += b)}/${len}|`,
    ]
    for (let i = 0; i < len; ++i) {
        str[0] += problem_id[i] + "|";
        str[1] += ":-:|";
        str[2] += (ac_status[i] === 1 ? 'O' : '-') + "|";
    }
    return str.join("\n");
}


(async function () {
    let res = template;
    const len = problem_id.length;
    for (let i = 0; i < len; ++i) {
        const code = ac_status[i] === 1 ? await get([repo_url, problem_code_path[i]].join("")) : "";
        res += 
`
## Problem ${problem_id[i]}. ${problem_name[i]}

${ac_status[i] == 1 ? `Solved By ${ac_author[i]}. ${ac_time[i]}` : `Upsolved By ${ac_author[i]}.`}

### 题意


### 思路


<details class = 'info' >
<summary>代码</summary>
<div>

\`\`\`${problem_code_suffix[i]}
${code}
\`\`\`

</div>
</details>
`
    }
    console.log(res);
})();

