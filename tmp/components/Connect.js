/* @flow */
'use strict';

import React from 'react-native';
import Component from './Component';
import PlayerActions from '../actions/Player';
import DeezerManager from '../services/DeezerManager';

const {
  StyleSheet,
  TouchableOpacity,
  Text,
  View,
  ActivityIndicatorIOS,
  Animated,
} = React;

class Connect extends Component {

  constructor() {
    super();

    this.connect = this.connect.bind(this);
    this._connectOpacity = new Animated.Value(0);
    this.state = {
      isLoggedIn: false,
      isPendding: false,
    };
  }

  componentDidMount() {
    Animated.timing(this._connectOpacity, {
      toValue: 1,
      duration: 600,
    }).start();
  }

  connect() {
    this.setState({ isPendding: true });
    this.props.connect && this.props.connect();
  }

  render() {
    return (
      <Animated.View style={[styles.container, { opacity: this._connectOpacity }]}>
        <TouchableOpacity onPress={this.connect} style={styles.buttonWrapper}>
          <View style={styles.button}>
          <ActivityIndicatorIOS
            style={{
              position: 'absolute',
              top: 0,
              left: -30,
            }}
            animating={this.state.isPendding}
            size="small" />
            <Text style={styles.buttonText}>Connect</Text>
          </View>
        </TouchableOpacity>
      </Animated.View>
    );
  }
}


const styles = StyleSheet.create({

  container: {
    flex: 1,
    backgroundColor: 'transaprent',
    justifyContent: 'flex-end',
    alignItems: 'center',
  },

  buttonWrapper: {
    backgroundColor: 'rgba(0,0,0,0.7)',
    alignSelf: 'stretch',
    justifyContent: 'center',
    marginHorizontal: 40,
    marginBottom: 40,
    alignItems: 'center',
    height: 40,
  },

  button: {
    flexDirection: 'row',
    alignItems: 'center',
    justifyContent: 'center',

  },

  buttonText: {
    fontSize: 18,
    color: '#fff',
  },

});

export default Connect;
