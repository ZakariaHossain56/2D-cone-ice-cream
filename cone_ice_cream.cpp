#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 600;

float rotateAngle = 0.0;
float translate_X = 0.0;
float translate_Y = 0.0;
float scale_X = 1.0;
float scale_Y = 1.0;

float cone_rotateAngle = 0.0;
float cone_translate_X = 0.0;
float cone_translate_Y = 0.0;
float cone_scale_X = 1.0;
float cone_scale_Y = 1.0;

float icecream_rotateAngle = 0.0;
float icecream_translate_X = 0.0;
float icecream_translate_Y = 0.0;
float icecream_scale_X = 1.0;
float icecream_scale_Y = 1.0;

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"uniform mat4 transform;\n"
"void main()\n"
"{\n"
"   gl_Position = transform * vec4(aPos, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 objectColor;\n"
"void main()\n"
"{\n"
"   FragColor = objectColor;\n"
"}\n\0";

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef _APPLE_
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CSE 4208: Assignment 1", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    // check for shader compile errors
    int success;
    char infoLog[512];
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // fragment shader
    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    // check for shader compile errors
    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    }
    // link shaders
    unsigned int shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    // check for linking errors
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------

    //triangle
    float vertices[] = {

        //cone outline -> 5, 1-22, 1 (24)  
        -0.0155475488590457,-0.984496124031007,0,   //5
        -0.1886941805874,-0.0503875968992248,0,     //1
        -0.035287695163227,-0.968992248062015,0,
        -0.0296429741238125,-0.976744186046511,0,
        -0.0239982530843978,-0.984496124031007,0,
        -0.0155475488590457,-0.984496124031007,0,   //5
        -0.00710230374495015,-0.980620155038759,0,
        -0.00147941915056222,-0.972868217054263,0,
        0.0013265640353751,-0.965116279069767,0,
        0.197188557702806,-0.0271317829457364,0,
        0.132470793754777,-0.0775193798449613,0,    //10
        0.107129599301234,-0.0852713178294575,0,
        0.0761491429195326,-0.0891472868217053,0,
        0.0451686865378317,-0.0930232558139534,0,
        0.0226280161589694,-0.0891472868217053,0,
        -0.00272409651708685,-0.0891472868217053,0,
        -0.0224424063762418,-0.0891472868217053,0,
        -0.0421661753466534,-0.0852713178294575,0,
        -0.0703406485424172,-0.0813953488372094,0,
        -0.0928813189212795,-0.0775193798449613,0,
        -0.115421989300142,-0.0736434108527133,0,   //20
        -0.137968118790261,-0.0658914728682171,0,
        -0.160506059613495,-0.0639534883720931,0,   //22
        -0.1886941805874,-0.0503875968992248,0,     //1

        //1st cream layer -> 14, 9-59, 9 (53)
        0.0226280161589694,-0.0891472868217053,0,   //14
        0.197188557702806,-0.0271317829457364,0,    //9
        0.132470793754777,-0.0775193798449613,0,    //10
        0.107129599301234,-0.0852713178294575,0,
        0.0761491429195326,-0.0891472868217053,0,
        0.0451686865378317,-0.0930232558139534,0,
        0.0226280161589694,-0.0891472868217053,0,   //14
        -0.00272409651708685,-0.0891472868217053,0,
        -0.0224424063762418,-0.0891472868217053,0,
        -0.0421661753466534,-0.0852713178294575,0,
        -0.0703406485424172,-0.0813953488372094,0,
        -0.0928813189212795,-0.0775193798449613,0,
        -0.115421989300142,-0.0736434108527133,0,   //20
        -0.137968118790261,-0.0658914728682171,0,
        -0.160506059613495,-0.0639534883720931,0,
        -0.202789605852167,-0.0426356589147287,0,
        -0.225346653564799,-0.0271317829457364,0,
        -0.239458456163336,-0.00775193798449613,0,
        -0.247941915056229,0.015503875968992,0,
        -0.253613931651927,0.0426356589147285,0,
        -0.253684900098264,0.0930232558139533,0,
        -0.25372311387706,0.120155038759689,0,
        -0.248127524838956,0.147286821705426,0,     //30
        -0.22555955890381,0.124031007751937,0,
        -0.202986133857408,0.0968992248062013,0,
        -0.180429086144776,0.0813953488372091,0,
        -0.143803908723659,0.0775193798449611,0,
        -0.115634894639152,0.0775193798449611,0,
        -0.0846380609236812,0.069767441860465,0,
        -0.0649088328420132,0.0620155038759688,0,
        -0.0282781963096406,0.0542635658914727,0,
        -0.000114641336390475,0.0581395348837208,0,
        0.0252265531171527,0.0658914728682169,0,    //40
        0.0477508461622446,0.073643410852713,0,
        0.0730865815045311,0.0852713178294571,0,
        0.0927885140299158,0.0968992248062013,0,
        0.109662626924337,0.116279069767441,0,
        0.126525821596244,0.143410852713178,0,
        0.137744295228737,0.17829457364341,0,
        0.146134949230265,0.220930232558139,0,
        0.174276667758489,0.240310077519379,0,
        0.196779124358554,0.263565891472868,0,
        0.224899006441751,0.2984496124031,0,        //50
        0.244655530079703,0.271317829457364,0,
        0.255972267714816,0.236434108527131,0,
        0.261660661644284,0.197674418604651,0,
        0.264543072387815,0.151162790697674,0,
        0.264586745277869,0.120155038759689,0,
        0.264635877279179,0.0852713178294571,0,
        0.259040288241074,0.0581395348837208,0,
        0.247805437274812,0.0348837209302325,0,
        0.22531389889726,0.00387596899224795,0,     //59
        0.197188557702806,-0.0271317829457364,0,    //9


        //2nd cream layer -> 38, 30-47, 60-74,30 (35)
        -0.0282781963096406,0.0542635658914727,0,   //38
        -0.248127524838956,0.147286821705426,0,     //30
        -0.22555955890381,0.124031007751937,0,
        -0.202986133857408,0.0968992248062013,0,
        -0.180429086144776,0.0813953488372091,0,
        -0.143803908723659,0.0775193798449611,0,
        -0.115634894639152,0.0775193798449611,0,
        -0.0846380609236812,0.069767441860465,0,
        -0.0649088328420132,0.0620155038759688,0,
        -0.0282781963096406,0.0542635658914727,0,   //38
        -0.000114641336390475,0.0581395348837208,0,
        0.0252265531171527,0.0658914728682169,0,    //40
        0.0477508461622446,0.073643410852713,0,
        0.0730865815045311,0.0852713178294571,0,
        0.0927885140299158,0.0968992248062013,0,
        0.109662626924337,0.116279069767441,0,
        0.126525821596244,0.143410852713178,0,
        0.137744295228737,0.17829457364341,0,
        0.146134949230265,0.220930232558139,0,      //47
        0.120799213887979,0.209302325581395,0,      //60
        0.0729228081668304,0.201550387596899,0,
        0.0475925319358008,0.186046511627906,0,
        0.0279124358554427,0.15891472868217,0,
        -0.00305710230374484,0.147286821705426,0,   //64
        -0.0340539360192159,0.155038759689922,0,
        -0.0650780652909705,0.182170542635658,0,
        -0.0960967354514682,0.205426356589147,0,
        -0.141178076209193,0.213178294573643,0,
        -0.180625614150016,0.220930232558139,0,
        -0.211644284310514,0.244186046511627,0,     //70
        -0.225750627797794,0.259689922480619,0,
        -0.2369800196528,0.232558139534883,0,
        -0.239758707282454,0.205426356589147,0,
        -0.242542854023365,0.182170542635658,0,     //74
        -0.248127524838956, 0.147286821705426, 0,     //30
        


        //3rd cream layer -> 85, 60-71, 75-96, 48-50, 60 (39)
        -0.0314663172835461,0.317829457364341,0,    //85
        0.120799213887979,0.209302325581395,0,      //60
        0.0729228081668304,0.201550387596899,0,
        0.0475925319358008,0.186046511627906,0,
        0.0279124358554427,0.15891472868217,0,
        -0.00305710230374484,0.147286821705426,0,
        -0.0340539360192159,0.155038759689922,0,
        -0.0650780652909705,0.182170542635658,0,
        -0.0960967354514682,0.205426356589147,0,
        -0.141178076209193,0.213178294573643,0,
        -0.180625614150016,0.220930232558139,0,
        -0.211644284310514,0.244186046511627,0,     //70
        -0.225750627797794,0.259689922480619,0,     //71
        -0.237050988099137, 0.282945736434108, 0,   //75
        -0.248378643956764, 0.325581395348837, 0,
        -0.248422316846817, 0.356589147286821, 0,
        -0.240015285511519, 0.387596899224806, 0,
        -0.214701386614259, 0.414728682170542, 0,
        -0.189321978381919, 0.395348837209302, 0,   //80
        -0.163942570149579, 0.375968992248061, 0,
        -0.135746260508789, 0.356589147286821, 0,
        -0.107555409979255, 0.341085271317829, 0,
        -0.0652745932962111, 0.321705426356589, 0,
        -0.0314663172835461, 0.317829457364341, 0,  //85
        -0.000485860901845125, 0.321705426356589, 0,
        0.0276667758488918, 0.333333333333333, 0,
        0.0586363140080793, 0.344961240310077, 0,
        0.0895949339447538, 0.364341085271317, 0,
        0.117747570695491, 0.375968992248061, 0,    //90
        0.148717108854679, 0.387596899224806, 0,
        0.188142810350475, 0.395348837209302, 0,
        0.244448083851949, 0.41860465116279, 0,
        0.244480838519489, 0.395348837209302, 0,
        0.241702150889835, 0.368217054263565, 0,
        0.23330603777705, 0.329457364341085, 0,     //96
        0.174276667758489, 0.240310077519379, 0,    //48
        0.196779124358554, 0.263565891472868, 0,
        0.224899006441751, 0.2984496124031, 0,      //50
        0.120799213887979, 0.209302325581395, 0,    //60



        //4th cream layer -> 105, 79-93, 97-110, 79 (31)
        -0.037263893438148, 0.434108527131782, 0,   //105
        -0.214701386614259, 0.414728682170542, 0,   //79
        -0.189321978381919, 0.395348837209302, 0,   //80
        -0.163942570149579, 0.375968992248061, 0,
        -0.135746260508789, 0.356589147286821, 0,
        -0.107555409979255, 0.341085271317829, 0,
        -0.0652745932962111, 0.321705426356589, 0,
        -0.0314663172835461, 0.317829457364341, 0,
        -0.000485860901845125, 0.321705426356589, 0,
        0.0276667758488918, 0.333333333333333, 0,
        0.0586363140080793, 0.344961240310077, 0,
        0.0895949339447538, 0.364341085271317, 0,
        0.117747570695491, 0.375968992248061, 0,    //90
        0.148717108854679, 0.387596899224806, 0,
        0.188142810350475, 0.395348837209302, 0,
        0.244448083851949, 0.41860465116279, 0,     //93
        0.241582050442188, 0.453488372093023, 0,    //97
        0.221792772136696, 0.503875968992247, 0,
        0.190757724642428, 0.53875968992248, 0,
        0.159815482039524, 0.507751937984495, 0,    //100
        0.120406157877497, 0.488372093023255, 0,
        0.0894475379408232, 0.468992248062015, 0,
        0.0528496560759909, 0.453488372093023, 0,
        0.0134348728027078, 0.43798449612403, 0,
        -0.037263893438148, 0.434108527131782, 0,   //105
        -0.0795174145649085, 0.434108527131782, 0,
        -0.135866360956436, 0.441860465116278, 0,
        -0.175324817119773, 0.457364341085271, 0,
        -0.209160388688721, 0.480620155038759, 0,
        -0.216158969319795, 0.449612403100775, 0,   //110
        -0.214701386614259, 0.414728682170542, 0,   //79


        //5th cream layer -> 118, 99-109, 111-129, 99 (32)  
        -0.0290097172180367, 0.573643410852713, 0,  //118
        0.190757724642428, 0.53875968992248, 0,     //99
        0.159815482039524, 0.507751937984495, 0,    //100
        0.120406157877497, 0.488372093023255, 0,
        0.0894475379408232, 0.468992248062015, 0,
        0.0528496560759909, 0.453488372093023, 0,
        0.0134348728027078, 0.43798449612403, 0,
        -0.037263893438148, 0.434108527131782, 0,
        -0.0795174145649085, 0.434108527131782, 0,
        -0.135866360956436, 0.441860465116278, 0,
        -0.175324817119773, 0.457364341085271, 0,
        -0.209160388688721, 0.480620155038759, 0,   //109
        -0.220477126323834, 0.515503875968992, 0,   //111
        -0.217703897805437, 0.546511627906976, 0,
        -0.209285948247625, 0.569767441860464, 0,
        -0.172660770826509, 0.565891472868217, 0,
        -0.130407249699749, 0.565891472868217, 0,
        -0.099421334206791, 0.565891472868217, 0,
        -0.0712577792335407, 0.569767441860464, 0,
        -0.0290097172180367, 0.573643410852713, 0,  //118
        0.00477672234960156, 0.585271317829457, 0,
        0.0357462605087889, 0.596899224806201, 0,   //120
        0.0667103395567203, 0.612403100775193, 0,
        0.0948575171962005, 0.627906976744185, 0,
        0.125805218910361, 0.655038759689922, 0,
        0.14830221639917, 0.682170542635658, 0,
        0.17641663937111, 0.720930232558139, 0,
        0.184916475597773, 0.686046511627906, 0,
        0.190604869527241, 0.647286821705426, 0,
        0.193487280270772, 0.600775193798449, 0,
        0.193530953160825, 0.569767441860464, 0,    //129
        0.190757724642428, 0.53875968992248, 0,     //99
        
        
        
        //6th cream layer -> 118, 113-125, 130-145, 113 (31)
        -0.0290097172180367, 0.573643410852713, 0,  //118
        -0.209285948247625, 0.569767441860464, 0,   //113
        -0.172660770826509, 0.565891472868217, 0,
        -0.130407249699749, 0.565891472868217, 0,
        -0.099421334206791, 0.565891472868217, 0,
        -0.0712577792335407, 0.569767441860464, 0,
        -0.0290097172180367, 0.573643410852713, 0,  //118
        0.00477672234960156, 0.585271317829457, 0,
        0.0357462605087889, 0.596899224806201, 0,   //120
        0.0667103395567203, 0.612403100775193, 0,
        0.0948575171962005, 0.627906976744185, 0,
        0.125805218910361, 0.655038759689922, 0,
        0.14830221639917, 0.682170542635658, 0,
        0.17641663937111, 0.720930232558139, 0,     //125
        0.170744622775412, 0.748062015503875, 0,    //130
        0.156605524620592, 0.786821705426356, 0,
        0.136838082760126, 0.821705426356588, 0,
        0.117097936455945, 0.837209302325581, 0,
        0.100240200895294, 0.806201550387596, 0,
        0.0805710230374494, 0.771317829457364, 0,
        0.063707828365542, 0.744186046511627, 0,
        0.0412053717654765, 0.720930232558139, 0,
        0.0130691123485098, 0.697674418604651, 0,
        -0.02635113003603, 0.686046511627906, 0,
        -0.0601430287149252, 0.67829457364341, 0,   //140
        -0.0967463696910141, 0.666666666666666, 0,
        -0.13617207118681, 0.65891472868217, 0,
        -0.158685446009389, 0.643410852713178, 0,
        -0.178371001201004, 0.620155038759689, 0,
        -0.195245114095425, 0.600775193798449, 0,   //145
        -0.209285948247625, 0.569767441860464, 0,   //113



        //7th cream layer -> 138, 133-143, 146-158, 133 (26)
        0.0130691123485098, 0.697674418604651, 0,   //138
        0.117097936455945, 0.837209302325581, 0,    //133
        0.100240200895294, 0.806201550387596, 0,
        0.0805710230374494, 0.771317829457364, 0,
        0.063707828365542, 0.744186046511627, 0,
        0.0412053717654765, 0.720930232558139, 0,
        0.0130691123485098, 0.697674418604651, 0,   //138
        -0.02635113003603, 0.686046511627906, 0,
        -0.0601430287149252, 0.67829457364341, 0,   //140
        -0.0967463696910141, 0.666666666666666, 0,
        -0.13617207118681, 0.65891472868217, 0,
        -0.158685446009389, 0.643410852713178, 0,   //143
        -0.161540561196637, 0.670542635658914, 0,   //146
        -0.161584234086691, 0.701550387596899, 0,
        -0.150365760454198, 0.736434108527131, 0,
        -0.127868762965389, 0.763565891472868, 0,
        -0.0997270444371654, 0.782945736434108, 0,  //150
        -0.0743913090948792, 0.794573643410852, 0,
        -0.0434272300469481, 0.810077519379844, 0,
        -0.012468610110274, 0.829457364341085, 0,
        0.00719510863631403, 0.868217054263565, 0,
        0.00706954907741028, 0.957364341085271, 0,
        0.0465116279069766, 0.953488372093023, 0,
        0.0775412162899878, 0.922480620155038, 0,
        0.10013101867016, 0.883720930232557, 0,     //158
        0.117097936455945, 0.837209302325581, 0,    //133


        //7th cream layer top -> 154-155, 159-162, 154 (7)
        //0.00719510863631403, 0.868217054263565, 0,  //154
        //0.00706954907741028, 0.957364341085271, 0,  //155
        //-0.012643301670488, 0.953488372093023, 0,   //159
        //-0.0351621356043234, 0.941860465116278, 0,  //160
        //-0.0125941696691778, 0.91860465116279, 0,
        //-0.00129380936783483, 0.895348837209302, 0, //162
        //0.00719510863631403, 0.868217054263565, 0,  //154



        //cone rectangle 1 -> 163-164, 2-8, 165 (10)
        -0.0213123703461075, -0.891472868217054, 0, //163
        -0.043814826946173, -0.914728682170542, 0,  //164
        -0.035287695163227,-0.968992248062015,0,    //2
        -0.0296429741238125,-0.976744186046511,0,
        -0.0239982530843978,-0.984496124031007,0,
        -0.0155475488590457,-0.984496124031007,0,
        -0.00710230374495015,-0.980620155038759,0,
        -0.00147941915056222,-0.972868217054263,0,
        0.0013265640353751,-0.965116279069767,0,    //8
        0.00971721803690355, -0.922480620155038, 0, //165
        


        //cone rectangle 2 -> 166-171 (6)
        -0.0243913090948793,-0.705426356589147,0,   //166
        -0.0722076645922044,-0.755813953488372,0,
        -0.0608527131782943,-0.817829457364341,0,
        -0.0213669614586745,-0.852713178294573,0,
        0.0377006223386832,-0.790697674418604,0,    //170
        0.0404847690795936,-0.767441860465116,0,    //171


        //cone rectangle 3 -> 172-174 (3)   
        -0.0892783054918656,-0.635658914728682,0,   //172
        -0.0413200131018669,-0.686046511627906,0,
        -0.075073698001965,-0.720930232558139,0,    //174


        //cone rectangle 4 -> 175-177 (3)
        -0.00188339338355701,-0.686046511627906,0,  //175
        0.0740637624194781,-0.608527131782945,0,
        0.0460803581176983,-0.740310077519379,0,    //177


        //cone rectangle 5 -> 178-181 (4)
        -0.0190140845070423,-0.523255813953488,0,   //178
        -0.0949721585325906,-0.593023255813953,0,
        -0.0216289987989954,-0.666666666666666,0,   //180
        0.0486898132983948,-0.593023255813953,0,    //181


        //cone rectangle 6 -> 182-184 (3)
        -0.129031553663063,-0.410852713178294,0,    //182
        -0.0415875095534445,-0.496124031007751,0,
        -0.103466535647996,-0.562015503875969,0,    //184


        //cone rectangle 7 -> 185-188 (4)
        0.0681679222622559,-0.422480620155038,0,    //185
        -0.00496779124358547,-0.496124031007751,0,
        0.0796648105688394,-0.585271317829457,0,
        0.104836772573425,-0.457364341085271,0,     //188


        //cone rectangle 8 -> 189-192 (4)
        -0.0221039414783273,-0.329457364341085,0,   //189
        -0.0952396549841685,-0.403100775193798,0,   //190
        -0.0218964952505732,-0.476744186046511,0,
        0.0484223168468172,-0.403100775193798,0,    //192


        //cone rectangle 9 -> 193-195 (3)
        0.0878589365651271,-0.403100775193798,0,    //193
        0.12442406376242,-0.364341085271317,0,
        0.11043236161153,-0.430232558139535,0,      //195
        

        //cone rectangle 10 -> 196-199 (4)
        -0.15176329293591,-0.271317829457364,0,     //196
        -0.115198165738618,-0.232558139534883,0,
        -0.0418495468937655,-0.310077519379844,0,
        -0.114985260399607,-0.383720930232558,0,    //199

        
        //cone rectangle 11 -> 200-203 (4)
        0.0679058849219349,-0.236434108527131,0,    //200
        -0.00241292717545569,-0.310077519379844,0,
        0.068113331149689,-0.383720930232558,0,
        0.135615241838629,-0.310077519379844,0,     //203
        
        
        //cone rectangle 12 -> 204-206 (3)
        -0.165978818648324,-0.17829457364341,0,     //204
        -0.132121410634348,-0.217054263565891,0,
        -0.157440768642865,-0.24031007751938,0,     //206
        
        
        //cone rectangle 13 -> 207-210 (4)
        -0.0223714379299049,-0.13953488372093,0,    //207
        -0.0955016923244892,-0.217054263565891,0,
        -0.0249754339993449,-0.290697674418604,0,
        0.0481602795064962,-0.217054263565891,0,    //210
        
        
        //cone rectangle 14 -> 211-214 (4)
        0.15791025221094,-0.13953488372093,0,       //211
        0.0847799978163555,-0.217054263565891,0,
        0.144016814062671,-0.275193798449612,0,
        0.169194235178513,-0.151162790697674,0,     //214
        
        
        //cone rectangle 15 -> 9-10, 215-216 (4)
        0.197188557702806,-0.0271317829457364,0,    //9
        0.132470793754777,-0.0775193798449613,0,    //10
        0.15786112020963, -0.104651162790697, 0,    //215
        0.185986461404084, -0.0736434108527133, 0,  //216


        //cone rectangle 16 -> 217-218, 11-14, 219 (7) 
        0.067851293809368,-0.197674418604651,0,     //217
        0.138170105906758,-0.124031007751938,0,     //218
        0.107129599301234,-0.0852713178294575,0,    //11
        0.0761491429195326,-0.0891472868217053,0,
        0.0451686865378317,-0.0930232558139534,0,
        0.0226280161589694,-0.0891472868217053,0,   //14
        -0.00267496451577678,-0.124031007751938,0,  //219

        
        //cone rectangle 17 -> 220-221, 18-21, 222 (7)
        -0.115247297739928,-0.197674418604651,0,    //220
        -0.0421115842340865,-0.124031007751938,0,   //221
        -0.0703406485424172,-0.0813953488372094,0,  //18
        -0.0928813189212795,-0.0775193798449613,0,
        -0.115421989300142,-0.0736434108527133,0,   //20
        -0.137968118790261,-0.0658914728682171,0,   //21
        -0.177328310950977,-0.120155038759689,0     //222

    };

    unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
    // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
    glBindVertexArray(0);


    // uncomment this call to draw in wireframe polygons.
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        // create transformations (total)
        /*glm::mat4 trans = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        trans = glm::translate(trans, glm::vec3(translate_X, translate_Y, 0.0f));
        trans = glm::rotate(trans, glm:: radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        trans = glm::scale(trans,glm::vec3(scale_X, scale_Y, 1.0));*/
        glm::mat4 translationMatrix;
        glm::mat4 rotationMatrix;
        glm::mat4 scaleMatrix;
        glm::mat4 modelMatrix;
        glm::mat4 identityMatrix = glm::mat4(1.0f);
        translationMatrix = glm::translate(identityMatrix, glm::vec3(translate_X, translate_Y, 0.0f));
        rotationMatrix = glm::rotate(identityMatrix, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        scaleMatrix = glm::scale(identityMatrix, glm::vec3(scale_X, scale_Y, 1.0f));
        modelMatrix = translationMatrix * rotationMatrix * scaleMatrix;

        // create transformations (cone)
        glm::mat4 cone_translationMatrix;
        glm::mat4 cone_rotationMatrix;
        glm::mat4 cone_scaleMatrix;
        glm::mat4 cone_modelMatrix;
        glm::mat4 cone_identityMatrix = glm::mat4(1.0f);
        cone_translationMatrix = glm::translate(modelMatrix, glm::vec3(cone_translate_X, cone_translate_Y, 0.0f));
        cone_rotationMatrix = glm::rotate(modelMatrix, glm::radians(cone_rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        cone_scaleMatrix = glm::scale(modelMatrix, glm::vec3(cone_scale_X, cone_scale_Y, 1.0f));
        cone_modelMatrix = cone_translationMatrix * cone_rotationMatrix * cone_scaleMatrix;


        // create transformations (icecream)
        glm::mat4 icecream_translationMatrix;
        glm::mat4 icecream_rotationMatrix;
        glm::mat4 icecream_scaleMatrix;
        glm::mat4 icecream_modelMatrix;
        glm::mat4 icecream_identityMatrix = glm::mat4(1.0f);
        icecream_translationMatrix = glm::translate(modelMatrix, glm::vec3(icecream_translate_X, icecream_translate_Y, 0.0f));
        icecream_rotationMatrix = glm::rotate(modelMatrix, glm::radians(icecream_rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        icecream_scaleMatrix = glm::scale(modelMatrix, glm::vec3(icecream_scale_X, icecream_scale_Y, 1.0f));
        icecream_modelMatrix = icecream_translationMatrix * icecream_rotationMatrix * icecream_scaleMatrix;


        //modelMatrix = rotationMatrix * scaleMatrix;
        //modelMatrix = translationMatrix * rotationMatrix;
        // get matrix's uniform location and set matrix


        //glm::vec3 pivotPoint(0.5388471177944862, 0.3761398018432699, 0.0f);
        //glm::mat4 translationToOrigin = glm::translate(identityMatrix, -pivotPoint);
        //glm::mat4 rotation_Matrix = glm::rotate(identityMatrix, glm::radians(rotateAngle), glm::vec3(0.0f, 0.0f, 1.0f));
        //glm::mat4 translationBack = glm::translate(identityMatrix, pivotPoint);
        //rotationMatrix = translationMatrix * translationBack * rotationMatrix * translationToOrigin * scaleMatrix;

        glUseProgram(shaderProgram);


        unsigned int transformLoc = glGetUniformLocation(shaderProgram, "transform");
        //glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        /*glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));*/

        int colorLoc = glGetUniformLocation(shaderProgram, "objectColor");
        // draw our first triangle
        glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(cone_modelMatrix));
        //cone shape
        glUniform4f(colorLoc, 0.99f, 0.90f, 0.64f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 0, 24);

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(icecream_modelMatrix));
        //1st cream layer
        glUniform4f(colorLoc, 0.98f, 0.84f, 0.32f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 24, 53);

        //2nd cream layer
        glUniform4f(colorLoc, 0.97f, 0.93f, 0.46f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 77, 35);

        //3rd cream layer
        glUniform4f(colorLoc, 0.72f, 0.84f, 0.44f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 112, 39);

        //4th cream layer
        glUniform4f(colorLoc, 0.82f, 0.88f, 0.52f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 151, 31);

        //5th cream layer
        glUniform4f(colorLoc, 0.95f, 0.f, 0.6f, 0.75f);
        glDrawArrays(GL_TRIANGLE_FAN, 182, 32);

        //6th cream layer 
        glUniform4f(colorLoc, 0.98f, 0.87f, 0.91f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 214, 31);

        //7th cream layer
        glUniform4f(colorLoc, 0.95f, 0.6f, 0.75f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 245, 26);

        glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(cone_modelMatrix));
        //cone rectangle
        glUniform4f(colorLoc, 0.95f, 0.67f, 0.28f, 1.0f);
        glDrawArrays(GL_TRIANGLE_FAN, 271, 10);
        glDrawArrays(GL_TRIANGLE_FAN, 281, 6);
        glDrawArrays(GL_TRIANGLE_FAN, 287, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 290, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 293, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 297, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 300, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 304, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 308, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 311, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 315, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 319, 3);
        glDrawArrays(GL_TRIANGLE_FAN, 322, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 326, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 330, 4);
        glDrawArrays(GL_TRIANGLE_FAN, 334, 7);
        glDrawArrays(GL_TRIANGLE_FAN, 341, 7);

        

        
        // glBindVertexArray(0); // no need to unbind it every time

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //translation (total)
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        translate_X += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        translate_X -= 0.001f;

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        translate_Y += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        translate_Y -= 0.001f;

    // Scale up when "Z" key is pressed
    if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS)
    {
        scale_X += 0.001f;
        scale_Y += 0.001f;
    }

    // Scale down when "X" key is pressed
    if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS)
    {
        scale_X -= 0.001f;
        scale_Y -= 0.001f;

        if (scale_X < 0.1f) scale_X = 0.1f;
        if (scale_Y < 0.1f) scale_Y = 0.1f;
    }

    // Rotate clockwise when "E" key is pressed
    if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
        rotateAngle -= 0.5236f;

    // Rotate counterclockwise when "Q" key is pressed
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        rotateAngle += 0.5236f;



    //translation (cone)
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
        cone_translate_X += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
        cone_translate_X -= 0.001f;

    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        cone_translate_Y += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        cone_translate_Y -= 0.001f;

    // Scale up when "C" key is pressed
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS)
    {
        cone_scale_X += 0.001f;
        cone_scale_Y += 0.001f;
    }

    // Scale down when "V" key is pressed
    if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS)
    {
        cone_scale_X -= 0.001f;
        cone_scale_Y -= 0.001f;

        if (cone_scale_X < 0.1f) cone_scale_X = 0.1f;
        if (cone_scale_Y < 0.1f) cone_scale_Y = 0.1f;
    }

    // Rotate clockwise when "E" key is pressed
    if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS)
        cone_rotateAngle -= 0.5236f;

    // Rotate counterclockwise when "Q" key is pressed
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
        cone_rotateAngle += 0.5236f;


    //translation (ice cream)
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        icecream_translate_X += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        icecream_translate_X -= 0.001f;

    if (glfwGetKey(window, GLFW_KEY_8) == GLFW_PRESS)
        icecream_translate_Y += 0.001f;
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        icecream_translate_Y -= 0.001f;

    // Scale up when "B" key is pressed
    if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS)
    {
        icecream_scale_X += 0.001f;
        icecream_scale_Y += 0.001f;
    }

    // Scale down when "N" key is pressed
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS)
    {
        icecream_scale_X -= 0.001f;
        icecream_scale_Y -= 0.001f;

        if (icecream_scale_X < 0.1f) icecream_scale_X = 0.1f;
        if (icecream_scale_Y < 0.1f) icecream_scale_Y = 0.1f;
    }

    // Rotate clockwise when "U" key is pressed
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS)
        icecream_rotateAngle -= 0.5236f;

    // Rotate counterclockwise when "Y" key is pressed
    if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS)
        icecream_rotateAngle += 0.5236f;
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}