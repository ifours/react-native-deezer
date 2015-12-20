/* @flow */
'use strict';

import React from 'react-native';
import Dimensions from 'Dimensions';

import AppStore from '../stores/App';
import TracksList from './TracksList';
import PlayerContainer from './PlayerContainer';
import PlayerFooter from './PlayerFooter';

const {
  Component,
  StyleSheet,
  View,
  Text,
  StatusBarIOS,
  Animated,
} = React;

const SCREEN_HEIGHT = Dimensions.get('window').height;

class ApplicationView extends Component {
  constructor(...args) {
    super(...args);

    this.isVisible = false;
    this._onChange = this._onChange.bind(this);
    this._styles = {
      player: {
        headerTop: new Animated.Value(-20),
        headerOpacity: new Animated.Value(0),
        containerTop: new Animated.Value(-SCREEN_HEIGHT),
        footerTop: new Animated.Value(150),
        // headerTop: new Animated.Value(0),
        // containerTop: new Animated.Value(0),
        // footerTop: new Animated.Value(0)
      },
      list: {
        containerTop: new Animated.Value(0),
      }
    };
  }

  componentWillMount() {
    this._setupStyles();
  }

  componentDidMount() {
    AppStore.addChangeListener(this._onChange);
  }

  componentWillUnmount() {
    AppStore.removeChangeListener(this._onChange);
  }

  _onChange() {
    let isVisible = AppStore.getPlayerVisbleStatus();

    if (isVisible && isVisible != this.isVisible) {
      StatusBarIOS.setHidden(false, 'fade');

      Animated.parallel([
        Animated.timing(this._styles.player.headerTop, {
          toValue: 0,
          duration: 300,
        }),
        Animated.timing(this._styles.player.headerOpacity, {
          toValue: 1,
          duration: 300,
        }),
        Animated.timing(this._styles.player.containerTop, {
          toValue: 0,
          duration: 300,
        }),
        Animated.timing(this._styles.player.footerTop, {
          toValue: 0,
          duration: 200,
        })
      ]).start(() => {
        Animated.timing(this._styles.list.containerTop, {
          toValue: 20,
          duration: 100,
        }).start();
      });
    }
  }

  onResponderMove(evt) {
    let offset = evt.nativeEvent.pageY - this._previousTop ;

    this._playerStyles.top = offset > 0 ? 0 : offset;
    this._updatePosition();
  }

  onResponderGrant(evt) {
    this._previousTop = evt.nativeEvent.pageY;
    this._previosTouchTime = Date.now();
  }

  onResponderRelease(evt) {
    this._styles.player.containerTop.setValue(this._playerStyles.top);

    if (this._playerStyles.top < -200 ||
      ((Date.now() - this._previosTouchTime) < 1000 && this._playerStyles.top < -40)) {

      StatusBarIOS.setHidden(true, 'fade');
      Animated.parallel([
        Animated.timing(this._styles.list.containerTop, {
          toValue: 0,
          duration: 200,
        }),
        Animated.timing(this._styles.player.headerTop, {
          toValue: -20,
          duration: 200,
        }),
        Animated.timing(this._styles.player.headerOpacity, {
          toValue: 0,
          duration: 100,
        }),
        Animated.timing(this._styles.player.footerTop, {
          toValue: 150,
          duration: 200,
        }),
        Animated.timing(this._styles.player.containerTop, {
          toValue: -SCREEN_HEIGHT,
          duration: 200,
        })
      ]).start(() => {
        this._setupStyles();
      });
    } else {
      Animated.timing(this._styles.player.containerTop, {
        toValue: 0,
        duration: 300,
      }).start(() => {
        this._setupStyles();
      });
    }

  }

  _setupStyles() {
    this._previousTop = 0;
    this._previosTouchTime = 0;

    this._playerStyles = {
      top: this._previousTop,
    };
  }

  _updatePosition() {
    this.player && this.player.setNativeProps({style: this._playerStyles});
  }

  render() {
    return (
      <View style={styles.container}>
        <View style={styles.container}>
          <View style={styles.headerView}>
            <Text style={styles.headerText}>Favorite tracks</Text>
          </View>
          <Animated.View style={[styles.favoriteTracksView, { paddingTop: this._styles.list.containerTop  }]}>
            <TracksList />
          </Animated.View>
        </View>

        {/** Player Views **/}
        <Animated.View style={[styles.playerContainerView, { top: this._styles.player.containerTop }]}
          onStartShouldSetResponder={(evt) => true}

          onResponderGrant={this.onResponderGrant.bind(this)}
          onResponderMove={this.onResponderMove.bind(this)}
          onResponderRelease={this.onResponderRelease.bind(this)}
          onResponderTerminationRequest={(evt) => false}

          ref={(player) => {
            this.player = player;
          }} >
          <PlayerContainer />
        </Animated.View>

        <Animated.View style={[styles.playerHeaderView, {
          top: this._styles.player.headerTop,
          opacity: this._styles.player.headerOpacity
        }]} >
          <Text style={styles.typeTitle} numberOfLines={1}>MIX</Text>
          <Text style={styles.playlistTitle} numberOfLines={1}>Favorite tracks</Text>
        </Animated.View>

        <Animated.View style={[{ top: this._styles.player.footerTop }]}>
          <PlayerFooter />
        </Animated.View>
        {/** end **/}
      </View>
    );
  }
};


const styles = StyleSheet.create({
  container: {
    flex: 1,
  },

  headerView: {
    justifyContent: 'center',
    paddingLeft: 15,
    height: 65,
  },

  headerText: {
    fontSize: 17,
    fontWeight: '400',
    color: '#3e3e44'
  },

  favoriteTracksView: {
    flex: 1,
    backgroundColor: '#eee',
  },
  playerContainerView: {
    position: 'absolute',
    left: 0,
    right: 0,
  },
  playerHeaderView: {
    position: 'absolute',
    alignItems: 'center',
    paddingTop: 24,
    left: 0,
    right: 0,
    backgroundColor: 'transparent',

    height: 60,
  },

  typeTitle: {
    color: '#d2d2d7',

    fontSize: 10,
    letterSpacing: 2,
    paddingBottom: 2,
  },

  playlistTitle: {
    color: '#fff',

    fontSize: 18,
    fontWeight: '500',
  },
});

export default ApplicationView;
