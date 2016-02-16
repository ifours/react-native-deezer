import React, {
  Component,
  View,
  Image,
  StyleSheet,
  Animated,
} from 'react-native';

export default class Cover extends Component {

  componentWillMount() {
    this.omImageLoad = this.omImageLoad.bind(this);

    this.opacity = new Animated.Value(0);
  }

  omImageLoad() {
    Animated.timing(this.opacity, {
      toValue: 1,
      duration: 200,
    }).start();
  }

  render() {
    let { style, ...props } = this.props;
    let defaultCover = require('../assets/cover.jpg');

    return (
      <View style={styles.container}>
        <Image style={style} source={defaultCover}>
          <Animated.Image {...props} style={[style, { opacity: this.opacity }]} onLoad={this.omImageLoad}>
            <View style={styles.equalizer}>
              {this.props.children}
            </View>
          </Animated.Image>
        </Image>
      </View>
    );
  }
}

const styles = StyleSheet.create({
  container: {

  },

  equalizer:{
    justifyContent: 'center',
    alignItems: 'center',
    flex: 1,
    backgroundColor: 'rgba(0,0,0,0)'
  }

});
