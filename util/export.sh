mkdir -p _site/wiki
mkdir -p _site/wiki/css
weewiki sync
weewiki export
rsync -rvt css/style.css _site/wiki/css
