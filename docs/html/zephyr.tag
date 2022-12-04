<?xml version='1.0' encoding='UTF-8' standalone='yes' ?>
<tagfile doxygen_version="1.9.1">
  <compound kind="file">
    <name>main.c</name>
    <path>/home/tatiana/projects/zephyros-rp2040-example3/ControlServos/src/</path>
    <filename>main_8c.html</filename>
    <includes id="servo_8c" name="servo.c" local="yes" imported="no">servo.c</includes>
    <member kind="function">
      <type>void</type>
      <name>demo_servos</name>
      <anchorfile>main_8c.html</anchorfile>
      <anchor>aa1fc04bb4c614ea829be2eb2241f7306</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>main</name>
      <anchorfile>main_8c.html</anchorfile>
      <anchor>a6288eba0f8e8ad3ab1544ad731eb7667</anchor>
      <arglist>(void)</arglist>
    </member>
  </compound>
  <compound kind="file">
    <name>mainpage.md</name>
    <path>/home/tatiana/projects/zephyros-rp2040-example3/ControlServos/src/</path>
    <filename>mainpage_8md.html</filename>
  </compound>
  <compound kind="file">
    <name>servo.c</name>
    <path>/home/tatiana/projects/zephyros-rp2040-example3/ControlServos/src/</path>
    <filename>servo_8c.html</filename>
    <member kind="define">
      <type>#define</type>
      <name>objeto_servo</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>af6cffce1346f5ea0772e84f63a1c418d</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MINPULSE</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a504a48856b2b1c8a48325df7088f49aa</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>MAXPULSE</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a7302231f8485e64ea42e2e726075b6ee</anchor>
      <arglist></arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>FGRADOS</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a0a6a6aa82dc3ec38066c14cd7241949e</anchor>
      <arglist>(x)</arglist>
    </member>
    <member kind="define">
      <type>#define</type>
      <name>STEP</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a70be2dc5c8bdc85b027ea6118753cca1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumeration">
      <type></type>
      <name>direction</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a99f26e6ee9fcd62f75203b5402df8098</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RIGTH</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a99f26e6ee9fcd62f75203b5402df8098ac2cd8d8289760e9d504f8e44fdf48e95</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>DOWN</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a99f26e6ee9fcd62f75203b5402df8098a9b0b4a95b99523966e0e34ffdadac9da</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LEFT</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a99f26e6ee9fcd62f75203b5402df8098adb45120aafd37a973140edee24708065</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>UP</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a99f26e6ee9fcd62f75203b5402df8098aba595d8bca8bc5e67c37c0a9d89becfa</anchor>
      <arglist></arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>calibracion</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a115c6b929ba1492d937c843cc943bbcc</anchor>
      <arglist>(int pulsador, int *grados, struct pwm_dt_spec servo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>min_max_pulse</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a0c6fa123afe4328571576d130fced1ab</anchor>
      <arglist>(struct pwm_dt_spec servo, int *min_pulse, int *max_pulse)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>servo_tapa</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>afaca9148de068830224dd17615aa480b</anchor>
      <arglist>(enum direction dir, struct pwm_dt_spec servo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>movimiento</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>ac0e394261f0cff4b4f2d2a7e7ca492b9</anchor>
      <arglist>(int grados, struct pwm_dt_spec servo)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>prueba_fun_camara</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a8baf985d647d74b4572ffa17c6b27e38</anchor>
      <arglist>(int *stop)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>servo_camara</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a0a8c3cbdccb1be8986515dc41392ba00</anchor>
      <arglist>(struct pwm_dt_spec servo, int seg, int *grados)</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>init_servos</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a534ab8eaf386e1d4304791b3712edd00</anchor>
      <arglist>()</arglist>
    </member>
    <member kind="variable">
      <type>const struct pwm_dt_spec</type>
      <name>servo0</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a6190848140e47640071699b31523e32e</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable">
      <type>const struct pwm_dt_spec</type>
      <name>servo1</name>
      <anchorfile>servo_8c.html</anchorfile>
      <anchor>a2febcf98052aa61b54400146eb4c8e51</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="page">
    <name>index</name>
    <title>Introduction</title>
    <filename>index.html</filename>
    <docanchor file="index.html">md__home_tatiana_projects_zephyros_rp2040_example3_ControlServos_src_mainpage</docanchor>
  </compound>
</tagfile>
