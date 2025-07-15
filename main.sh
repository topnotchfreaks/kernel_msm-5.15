#!/bin/bash

# Masuk ke direktori kerja
# git clone https://github.com/vkyas/kernel_msm-5.15.git
# cd kernel_msm-5.15 || exit

# Tambahkan remote upstream dari repo asli
git remote add upstream https://github.com/topnotchfreaks/kernel_msm-5.15.git

# Ambil semua branch dari upstream
git fetch upstream

# Loop semua branch dari upstream dan push ke origin (fork kamu)
for branch in $(git branch -r | grep 'upstream/' | sed 's/upstream\///'); do
    echo "Syncing branch: $branch"
    git checkout -B $branch upstream/$branch
    git push origin $branch
done

echo "✅ Semua branch berhasil disinkronkan ke fork kamu: https://github.com/vkyas/kernel_msm-5.15"
