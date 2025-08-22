#!/bin/bash

# 颜色定义
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# 第一阶段：查找所有Git仓库
echo -e "${BLUE}🔍 正在搜索主目录下的Git仓库...${NC}"
repo_list=()
while IFS= read -r -d '' gitdir; do
    repo_path=$(dirname "$gitdir")
    repo_list+=("$repo_path")
done < <(find ~ -type d -name ".git" -print0 2>/dev/null)

total_repos=${#repo_list[@]}
echo -e "${GREEN}✅ 共找到 ${total_repos} 个Git仓库${NC}"
echo ""

# 第二阶段：逐个处理仓库
for ((i=0; i<${total_repos}; i++)); do
    repo_path="${repo_list[$i]}"
    echo -e "${BLUE}🔄 处理仓库 ($((i+1))/${total_repos}): ${YELLOW}${repo_path}${NC}"
    
    # 进入仓库目录并执行pull
    (cd "$repo_path" && git pull)
    exit_code=$?
    
    # 显示结果状态
    if [ $exit_code -eq 0 ]; then
        echo -e "${GREEN}✔ 更新成功${NC}"
    else
        echo -e "${RED}✖ 更新失败 (退出码: ${exit_code})${NC}"
    fi
    
    echo "----------------------------------------"
done

echo -e "${GREEN}🎉 所有Git仓库处理完成${NC}"
