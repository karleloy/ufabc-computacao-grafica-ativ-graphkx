#include "window.hpp"
#include "card.hpp"

#include <vector>
#include <algorithm>
#include <random>
#include <iostream>
#include <chrono>
#include <thread>
#include <map>

void Window::restartGame() {
  // Dicionário de fórmulas matemáticas associadas a operações
  formulas = {
      {"ADIÇÃO", "a + b"},
      {"SUBTRAÇÃO", "a - b"},
      {"MULTIPLICAÇÃO", "a * b"},
      {"DIVISÃO", "a / b"},
      {"EXPONENCIAÇÃO", "a^b"},
      {"RAIZ", "sqrt(a)"},
      {"LOGARITMO", "log(a)"},
      {"FATORIAL", "a!"},
      {"SENO", "sin(a)"},
      {"COSSENO", "cos(a)"}
  };

  // Vector para armazenar os nomes das operações
  std::vector<std::string> uniqueCardValues;
  for (const auto& [name, _] : formulas) {
      uniqueCardValues.push_back(name);
  }

  // Embaralhar os valores das cartas para aleatoriedade
  std::shuffle(uniqueCardValues.begin(), uniqueCardValues.end(), std::mt19937(std::random_device()()));

  // Limpar o tabuleiro
  m_board.clear();

  // Cria pares de cartas com valores únicos e distribui no tabuleiro
  for (size_t i = 0; i < m_N * m_N / 2; ++i) {
      const std::string& value = uniqueCardValues[i];

      // Cria dois objetos Card com o mesmo valor
      Card card1(value);
      Card card2(value);

      // Adiciona os objetos Card ao tabuleiro
      m_board.push_back(card1);
      m_board.push_back(card2);
  }

  // Embaralhar o tabuleiro para aleatoriedade
  std::shuffle(m_board.begin(), m_board.end(), std::mt19937(std::random_device()()));

  // Reiniciar variáveis do jogo
  m_matches = 0;
  m_noneRevealed = true;
  m_gameState = GameState::Play;
}

void Window::onCreate() {
  // Carregar a fonte com tamanho maior para as cartas
  auto const filename{abcg::Application::getAssetsPath() + "Inconsolata-Medium.ttf"};
  m_font = ImGui::GetIO().Fonts->AddFontFromFileTTF(filename.c_str(), 52.0f);
  if (m_font == nullptr) {
    throw abcg::RuntimeError{"Não foi possível carregar o arquivo de fonte"};
  }
  restartGame();
}

void Window::onPaintUI() {
  // Obtém o tamanho da janela da aplicação
  auto const appWindowWidth{gsl::narrow<float>(getWindowSettings().width)};
  auto const appWindowHeight{gsl::narrow<float>(getWindowSettings().height)};

  // Janela "Memória Matemática"
  {
    ImGui::SetNextWindowSize(ImVec2(appWindowWidth, appWindowHeight));
    ImGui::SetNextWindowPos(ImVec2(0, 0));

    auto const flags{ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoResize |
                     ImGuiWindowFlags_NoCollapse};
    ImGui::Begin("Memória Matemática", nullptr, flags);

    // Texto estático exibindo mensagens
    {
      std::string text;
      switch (m_gameState) {
      case GameState::Play:
        text = m_noneRevealed ? "Clique em uma carta" : "Ache o par desta carta";
        break;
      case GameState::Win:
        text = "Você venceu!";
        break;
      case GameState::Wait:
        text = "Errou! Clique em qualquer carta para tentar de novo.";
        break;
      }
      ImGui::SetCursorPosX((appWindowWidth - ImGui::CalcTextSize(text.c_str()).x) / 2);
      ImGui::Text("%s", text.c_str());
      ImGui::Spacing();
    }

    ImGui::Spacing();
    // Tabuleiro do jogo
    {
      auto const gridHeight{appWindowHeight - 22 - 60 - (m_N * 10) - 60};
      auto const buttonHeight{gridHeight / m_N};

      std::string button_label;

      // Usa a fonte personalizada
      ImGui::PushFont(m_font);
      if (ImGui::BeginTable("Tabuleiro do jogo", m_N)) {
        for (auto i : iter::range(m_N)) {
          ImGui::TableNextRow();
          for (auto j : iter::range(m_N)) {
            ImGui::TableSetColumnIndex(j);
            auto const offset{i * m_N + j};

            // Obter o valor da carta (fórmula matemática ou espaço em branco)
            if (m_board.at(offset).isFaceUp()) {
              button_label = formulas[m_board.at(offset).getValue()];
            } else {
              button_label = " ";
            }

            // Texto do botão com um ID no formato ##ij
            auto buttonText{fmt::format("{}##{}{}", button_label, i, j)};
            if (ImGui::Button(buttonText.c_str(), ImVec2(-1, buttonHeight))) {
              if (m_gameState == GameState::Play && button_label == " ") {
                
                // Virar a carta
                m_board.at(offset).flip();

                if (m_noneRevealed) {
                  current_card_offset = offset;
                } else {
                  last_card_offset = current_card_offset;
                  current_card_offset = offset;
                  checkEndCondition();
                }
                m_noneRevealed = !m_noneRevealed;
              }
              else if (m_gameState == GameState::Wait) {
                m_board.at(current_card_offset).flip();
                m_board.at(last_card_offset).flip();
                m_gameState = GameState::Play;
              }
            }
          }
          ImGui::Spacing();
        }
        ImGui::EndTable();
      }
      ImGui::PopFont();
    }

    ImGui::Spacing();
    // Botão "Reiniciar jogo"
    {
      if (ImGui::Button("Reiniciar jogo", ImVec2(-1, 50))) {
        restartGame();
      }
    }

    ImGui::End();
  }
}

bool Window::checkEndCondition() {
  if (m_gameState != GameState::Play) {
    return false;
  }
  if (m_board.at(current_card_offset) == m_board.at(last_card_offset)) {
    m_matches += 1;
    if (m_matches == (m_N * m_N) / 2) {
      m_gameState = GameState::Win;
      return true;
    }
  } else {
    m_gameState = GameState::Wait;
  }
  return false;
}
