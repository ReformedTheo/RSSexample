#include <opencv2/opencv.hpp>
#include <iostream>
#include <string>

int main() {
    cv::VideoCapture cap(0); // Abre a webcam padrão

    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a câmera" << std::endl;
        return -1;
    }

    cv::Mat frame;
    std::cout << "Capturando imagem..." << std::endl;

    // Captura um frame
    if (cap.read(frame)) {
        std::string imagePath = "captura.jpg"; // Nome do arquivo para salvar a imagem
        cv::imwrite(imagePath, frame); // Salva o frame capturado como uma imagem
        std::cout << "Imagem salva em: " << imagePath << std::endl;
    } else {
        std::cerr << "Falha ao capturar a imagem" << std::endl;
        return -1;
    }

    return 0;
}
