import React from "react"
import logo from './logo.svg';
import './App.css';
import { SketchPicker } from 'react-color';
import { HexColorPicker } from "react-colorful";
import hexRgb from 'hex-rgb';

class App extends React.Component {

  constructor(props) {
    super(props);
    this.state = {
      devices: [],
      device: {},
      connected: false
    }
  }

  componentDidMount() {
    this.handleRefreshDevices()
  }

  handleRefreshDevices() {
    window.bluetoothSerial.list(devices => {
      console.log(devices)
      this.setState({ devices })
    })
  }

  handleConnect(device) {
    window.bluetoothSerial.connect(
      device.address,
      () => {
        console.log("connected")
        this.setState({ connected: true, device })
      },
      (err) => {
        console.log(err)
        this.setState({ connected: false })
      })
  }

  renderList() {
    return <div>
      <button onClick={() => this.handleRefreshDevices()}>
        refresh
      </button>
      <div>
        {this.state.devices.map(d => <li>
          <button onClick={() => this.handleConnect(d)}>connect</button> - {d.name}
        </li>)}
      </div>
    </div>
  }

  handleChangeComplete(color){
    console.log(color)
    const rgbcol = hexRgb(color)
    console.log(rgbcol)
    window.bluetoothSerial.write(`r=${rgbcol.red}\n`);
    window.bluetoothSerial.write(`g=${rgbcol.green}\n`);
    window.bluetoothSerial.write(`b=${rgbcol.blue}\n`);
    
  }

  renderColorPicker(){
    return <div>
      <div  style={{textAlign: "center", padding:20}}>Connected to {this.state.device.name}</div>
      <div style={{display: "flex", justifyContent: "center", padding: 20}}>
      <HexColorPicker onChange={this.handleChangeComplete} />;
      </div>
    </div>
  }

  render() {
    return <div className="App">
        {!this.state.connected && this.renderList()}
        {this.state.connected && this.renderColorPicker()}
    </div>
  }
}



export default App;
