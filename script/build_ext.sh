export API_URL=https://reddit-account-age.adamkrasny.com
parcel build -d dist/extension src/extension/Background.bs.js
parcel build -d dist/extension src/extension/Inject.bs.js
cp src/extension/manifest.json dist/extension
cp src/extension/menu.html dist/extension
cp src/extension/menu.css dist/extension
