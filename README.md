# Deezer Player

This project was build as part of [RSConf 2016](http://2016.conf.rollingscopes.com/) workshops. We tried to build a streaming music app using Deezer iOS SDK and React Native.

## Demo

### Mobile App (iOS)
<img src="assets/deezer.gif" width="320" />

## Running the project
- [react-native requirements](https://facebook.github.io/react-native/docs/getting-started.html#requirements)
- `npm install` to install all dependencies
- create free [Deezer](http://www.deezer.com/) account and add some amazing songs to your library :)
- go to [Deezer Developer](http://developers.deezer.com/) and create new ios application
  * copy Application ID from settings section and replace @"YOUR_APPLICATION_ID" in `ios/DeezerSession.h`
  * make sure iOS bundle ID match your project bundle identifier
- open Deezer.xcodeproj and run Deezer application
